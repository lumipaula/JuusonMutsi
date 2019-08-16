#pragma once

#include <vector>
#include <list>
#include <future>
#include <thread>
#include "blockingconcurrentqueue.h"
#include "task.h"
#include <iostream>
#include <utility>
#include <atomic>
#include <mutex>
#include <unordered_map>

template<typename RT>
class Task;

using taskptr = std::unique_ptr<Task<void()>>;

enum ThreadState{
    TS_WORK = 0,
    TS_IDLE = 1,
    TS_LOST = 2
};


class HThread;
class ThreadPool;

class HThread : public std::thread{
private:
    ThreadState m_state;
    bool m_running;
    taskptr m_currentTask;
public:
    HThread(std::function<void()> fun);

    void workerMain();
};




class ThreadPool{
private:
    bool m_running = false;
    size_t m_threadCount;
    std::list<HThread> m_threads;
    moodycamel::BlockingConcurrentQueue<taskptr> m_taskQueue;
    
    std::mutex m_returnMutex;



public:
    ThreadPool();
    ThreadPool(size_t count);
    ~ThreadPool();

    void setSize(size_t count){ m_threadCount = count; }

    void start();
    void stop();

    void TpMain();

    void workerMain();

    void enqueue(taskptr task);

    template<typename T>
    void enqueue(TaskWrapper<T> &rapper){

    }

};

