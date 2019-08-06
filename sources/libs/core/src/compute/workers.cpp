#include "workers.h"
#include "iostream"

void queueFlush(){

};


void dummyFuck(){

}


HThread::HThread(std::function<void()> fun) :
    std::thread(fun){

}


ThreadPool::ThreadPool(size_t count){
    m_running = true;
    for(int i=0;i<count;i++){
        m_threads.emplace_back(std::bind(&ThreadPool::workerMain,this));
        
    }
}

ThreadPool::~ThreadPool(){
    m_running = false;
    //Empty the queue
    for(int i=0;i<m_threads.size();i++){
        //enqueue(queueFlush);
    }
    for(auto &t : m_threads){
        t.join();
    }
}

void ThreadPool::start(){

}
void ThreadPool::stop(){

}

void ThreadPool::TpMain(){

}

void ThreadPool::workerMain(){
    while(m_running){
        void *task;
        m_taskQueue.wait_dequeue(task);
        Task<void()> *t = (Task<void()>*)task;
        t->execute();
    }
}

HThread& ThreadPool::getThread(int id){
    std::list<HThread>::iterator it = m_threads.begin();
    std::advance(it,id);
    return *it;
}

HThread ThreadPool::detachThread(int id){

}