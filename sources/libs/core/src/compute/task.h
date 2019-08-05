#pragma once
#include <memory>
#include <future>
#include <functional>





template<class F, class... Args>
class Task : public std::packaged_task<F(Args...)>{
private:

public:
    Task(F&& f, Args&&... args) :
    std::packaged_task<F(Args...)>(std::bind(std::forward<F>(f),std::forward<Args>(args)...)) {
        
    }
};

template<typename T>
struct TaskCookie{
    T m_value;
    std::unique_ptr<Task<void>> m_task;
};