#include <vector>
#include <list>
#include <future>
#include <thread>
#include "blockingconcurrentqueue.h"
#include "task.h"
#include <iostream>
#include <utility>
#include <atomic>

#define QNAMED(var) #var, var






class HThread;

class HThread : public std::thread{
private:
public:
    HThread(std::function<void()> fun);
};


class ThreadPool{
private:
    bool m_running = false;
    std::list<HThread> m_threads;
    moodycamel::BlockingConcurrentQueue<void*> m_taskQueue;
public:
    ThreadPool(size_t count);
    ~ThreadPool();

    void start();
    void stop();

    void TpMain();

    void workerMain();

    HThread& getThread(int id);
    HThread detachThread(int id);



    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> TaskCookie<typename std::result_of<F(Args...)>::type> {
        using rt = typename std::result_of<F(Args...)>::type;

        std::cout << "pillu" << std::endl;



        auto task = new Task<typename std::result_of<F(Args...)>::type(Args...)>(std::forward<F>(f),std::forward<Args>(args)...);
    
        //task->execute();

        TaskCookie tc(task->get_future());


        m_taskQueue.enqueue(std::move(task));
        return std::move(tc);
    }


};