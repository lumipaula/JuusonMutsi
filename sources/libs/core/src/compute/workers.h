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

#define QNAMED(var) #var, var



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
public:
    HThread(std::function<void()> fun);
};

struct WorkTicket{
    ThreadPool *m_pool;
    WorkTicket(ThreadPool *pool);
    ~WorkTicket();
};


class ThreadPool{
private:
    bool m_running = false;
    size_t m_threadCount;
    std::list<HThread> m_threads;
    std::atomic<uint64_t> m_ticketCount = 0;
    std::atomic_int m_threadStates[3] {0,0,0};
    moodycamel::BlockingConcurrentQueue<std::unique_ptr<Task<void()>>> m_taskQueue;
    
    std::list<std::unique_ptr<Task<void()>>> m_returnedTasks;
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

    HThread& getThread(int id);
    HThread detachThread(int id);

    WorkTicket issueTicket(){
        WorkTicket wt(this);
        m_ticketCount++;
        m_threadStates[TS_IDLE]--;
        m_threadStates[TS_WORK]++;
        return wt;
    }

    void releaseTicket(){
        m_threadStates[TS_WORK]--;
        m_threadStates[TS_IDLE]++;
    }

    void returnTask(std::unique_ptr<Task<void()>> task);
    std::list<std::unique_ptr<Task<void()>>> getReturns(int id);

    void enqueueList(std::list<std::unique_ptr<Task<void()>>> &tasks);

    void enqueue(std::unique_ptr<Task<void()>> task);

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> TaskCookie<typename std::result_of<F(Args...)>::type> {
        using rt = typename std::result_of<F(Args...)>::type;
        auto task = createTask(std::forward<F>(f),std::forward<Args>(args)...);
        m_taskQueue.enqueue(std::move(std::get<1>(task)));
        return std::move(std::get<0>(task));
    }

    template<class F, class... Args>
    auto enqueue(std::string name,F&& f, Args&&... args) -> TaskCookie<typename std::result_of<F(Args...)>::type> {
        using rt = typename std::result_of<F(Args...)>::type;
        auto task = createTaskn(name,std::forward<F>(f),std::forward<Args>(args)...);
        m_taskQueue.enqueue(std::move(std::get<1>(task)));
        return std::move(std::get<0>(task));
    }

    template<class F,class... Args>
    auto enqueue(std::tuple<TaskCookie<typename std::result_of<F(Args...)>::type>,std::unique_ptr<Task<void()>>> cookietask)
    -> TaskCookie<typename std::result_of<F(Args...)>::type> {
        m_taskQueue.enqueue(std::move(std::get<1>(cookietask)));
        return std::move(std::get<0>(cookietask));
    }


};

#define named(fun) #fun,fun
