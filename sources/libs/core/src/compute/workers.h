#include <vector>
#include <future>
#include <thread>
#include "blockingconcurrentqueue.h"
#include "task.h"

class HThread : public std::thread{
private:
public:
    HThread(std::function<void()> fun);
};


class ThreadPool{
private:
    std::vector<HThread> m_threads;
    moodycamel::BlockingConcurrentQueue<TaskCookie> m_taskQueue;
public:
    ThreadPool(size_t count);
    ~ThreadPool();

    void start();
    void stop();

    void TpMain();

    void workerMain();


    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        TaskCookie tc;
        auto task = std::make_unique<Task>(std::forward(f),std::forward(args)...);
        auto retVal = task->get_future();
        tc.m_task = std::move(task);
        m_taskQueue.enqueue(std::move(tc));
        return retVal;
    }


};