#include "workers.h"
#include "iostream"

void queueFlush(){

};




WorkTicket::WorkTicket(ThreadPool *pool) :
    m_pool(pool){
    
}

WorkTicket::~WorkTicket(){
    m_pool->releaseTicket();
}

HThread::HThread(std::function<void()> fun) :
    std::thread(fun){
    m_state = TS_IDLE;
}


ThreadPool::ThreadPool() :
    m_threadCount(0){

}

ThreadPool::ThreadPool(size_t count) :
    m_threadCount(count){
    start();
}

ThreadPool::~ThreadPool(){
    stop();
}

void ThreadPool::start(){
    if(m_threadCount < 1){
        std::cout << "Not enough threads spawned to start pool" << std::endl;
        return;
    }
    m_running = true;
    for(int i=0;i<m_threadCount;i++){
        m_threads.emplace_back(std::bind(&ThreadPool::workerMain,this));
        
    }
}
void ThreadPool::stop(){
    if(!m_running)
        return;
    m_running = false;
    //Empty the queue
    for(int i=0;i<m_threads.size();i++){
        enqueue(named(queueFlush));
    }
    for(auto &t : m_threads){
        t.join();
    }

    m_threads.clear();
}

void ThreadPool::TpMain(){

}

void ThreadPool::workerMain(){
    while(m_running){
        std::unique_ptr<Task<void()>> task;
        m_taskQueue.wait_dequeue(task);
        std::cout << (*task) << std::endl;
        task->execute();
        if(task->returnable()){
            returnTask(std::move(task));
            continue;
        }
        if(task->repeatable()){
            task->reset();
            enqueue(std::move(task));
            continue;
        }
    }
}

HThread& ThreadPool::getThread(int id){
    std::list<HThread>::iterator it = m_threads.begin();
    std::advance(it,id);
    return *it;
}

HThread ThreadPool::detachThread(int id){

}

void ThreadPool::returnTask(std::unique_ptr<Task<void()>> task){
    task->reset();
    std::lock_guard<std::mutex> lock(m_returnMutex);
    m_returnedTasks.push_back(std::move(task));
}

void ThreadPool::enqueue(std::unique_ptr<Task<void()>> task){
    m_taskQueue.enqueue(std::move(task));
}

void ThreadPool::enqueueList(std::list<std::unique_ptr<Task<void()>>> &tasks){
    auto it = tasks.begin();
    std::vector<TaskCookie<void>> cookies;
    while(*it){
        (*it)->setReturn(true,609);
        enqueue(std::move(*it));
        it++;
    }
}