#include "workers.h"
#include "iostream"

void queueFlush(){

};




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
        //enqueue(queueFlush);
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
        task->execute();
        std::cout << *task << " Finished succesfully" << std::endl;
        if(task->callback()){
            task->reset();
            task->m_callbackFun(std::move(task));
            continue;
        }

        if(task->returnable()){

            continue;
        }
        if(task->repeatable()){
            task->reset();
            continue;
        }
    }
}
