#pragma once
#include <memory>
#include <future>
#include <functional>
#include <ostream>
#include <iostream>
#include <tuple>
#include <string>

template<typename RT>
class Task;

template<class T>
struct TaskCookie{
    std::future<T> m_value;

    TaskCookie<T>(){

    }

    TaskCookie<T>(std::future<T> value) :
        m_value(std::move(value)){

    }

    T waitAndGet(){
        m_value.wait();
        return m_value.get();
    }

    void wait(){
        m_value.wait();
    }



};


template<typename RT>
class Task : public std::packaged_task<RT>{
friend std::ostream &operator <<(std::ostream &output, Task<void()> const& task);
private:
    bool m_repeat;
    bool m_return;
    int m_returnId;
    std::string m_functionName;
public:

    template<class F, class... Args>
    Task(F&& f, Args&&... args)   :
        std::packaged_task<RT>(std::bind(std::forward<F>(f),std::forward<Args>(args)...)),
        m_repeat(false),
        m_return(false)
        {
    }

    template<class F, class... Args>
    Task(std::string name, F&& f, Args&&... args)   :
        std::packaged_task<RT>(std::bind(std::forward<F>(f),std::forward<Args>(args)...)),
        m_functionName(name),
        m_repeat(false),
        m_return(false)
        {
    }

    bool execute(){
        (*this)();
    }

    void setRepeat(bool rep){
        m_repeat = rep;
    }

    void setReturn(bool ret, int id){
        m_return = ret;
    }

    bool returnable(){
        return m_return;
    }
    bool repeatable(){
        return m_repeat;
    }



};




template<class F,class... Args>
auto createTask(F&& f, Args&&... args) 
    -> std::tuple<TaskCookie<typename std::result_of<F(Args...)>::type>,std::unique_ptr<Task<void()>>> {
    using rt = typename std::result_of<F(Args...)>::type;

    auto task = new Task<rt(Args...)>(std::forward<F>(f),std::forward<Args>(args)...);

    TaskCookie tc(task->get_future());

    std::unique_ptr<Task<void()>> realTask = std::unique_ptr<Task<void()>>(reinterpret_cast<Task<void()>*>(task));

    return std::make_tuple(std::move(tc),std::move(realTask));


}

template<class F,class... Args>
auto createTaskn(std::string name, F&& f, Args&&... args) 
    -> std::tuple<TaskCookie<typename std::result_of<F(Args...)>::type>,std::unique_ptr<Task<void()>>> {
    using rt = typename std::result_of<F(Args...)>::type;

    auto task = new Task<rt(Args...)>(name,std::forward<F>(f),std::forward<Args>(args)...);

    TaskCookie tc(task->get_future());

    std::unique_ptr<Task<void()>> realTask = std::unique_ptr<Task<void()>>(reinterpret_cast<Task<void()>*>(task));

    return std::make_tuple(std::move(tc),std::move(realTask));


}

