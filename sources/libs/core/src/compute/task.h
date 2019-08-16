#pragma once
#include <memory>
#include <future>
#include <functional>
#include <ostream>
#include <iostream>
#include <tuple>
#include <string>
#include "workers.h"





template<typename RT>
class Task;

class ThreadPool;

using taskptr = std::unique_ptr<Task<void()>>;




struct TaskInfo{
    std::string m_functionName;

};

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

template<class T>
struct TaskWrapper{
    TaskCookie<T> m_cookie;
    taskptr m_task;

    ThreadPool *m_pool;

    TaskWrapper(TaskCookie<T> cookie, taskptr task) :
        m_cookie(std::move(cookie)),
        m_task(std::move(task)){
        
    }

    TaskWrapper(TaskCookie<T> cookie, taskptr task, ThreadPool *pool) :
        m_cookie(std::move(cookie)),
        m_task(std::move(task)),
        m_pool(pool){
        
    }

    void setPool(ThreadPool *pool){
        m_pool = pool;
    }



};


template<typename RT>
class Task : public std::packaged_task<RT>{
friend std::ostream &operator <<(std::ostream &output, Task<void()> const& task);
private:
    int m_repeats;
    bool m_repeat;
    bool m_return;
    int m_returnId;
    std::string m_functionName;


    //function for returning the Task pointer
    bool m_callback;


public:

    std::function<void(taskptr)> m_callbackFun;

    template<class F, class... Args>
    Task(F&& f, Args&&... args)   :
        std::packaged_task<RT>(std::bind(std::forward<F>(f),std::forward<Args>(args)...)),
        m_repeat(false),
        m_return(false),
        m_callback(false)
        {
    }

    template<class F, class... Args>
    Task(std::string name, F&& f, Args&&... args)   :
        std::packaged_task<RT>(std::bind(std::forward<F>(f),std::forward<Args>(args)...)),
        m_functionName(name),
        m_repeat(false),
        m_return(false),
        m_callback(false)
        {
    }

    bool execute(){
        try{
            (*this)();
            return true;
        }
        catch(...){
            return false;
        }
    }

    void setRepeat(bool rep, int times){
        m_repeat = rep;
        m_repeats = times;
    }

    void setReturn(bool ret, int id){
        m_return = ret;
    }

    void setCallback(bool callback){
        m_callback = callback;
    }

    void setCallbackFun(std::function<void(taskptr)> fun){
        m_callbackFun = std::move(fun);
    }

    bool returnable(){
        return m_return;
    }
    bool repeatable(){
        if(m_repeat && m_repeats > 0){
            m_repeats--;
            return true;
        }
        return false;
    }

    bool callback(){
        return m_callback;
    }




};



template<class F,class... Args>
auto createTaskNameless(F&& f, Args&&... args) 
    -> TaskWrapper<typename std::result_of<F(Args...)>::type>{
    using rt = typename std::result_of<F(Args...)>::type;
    std::cout << f << std::endl;
    auto task = new Task<rt(Args...)>(std::forward<F>(f),std::forward<Args>(args)...);

    TaskCookie tc(task->get_future());

    taskptr realTask = taskptr(reinterpret_cast<Task<void()>*>(task));

    return TaskWrapper(std::move(tc),std::move(realTask));


}

template<class F,class... Args>
auto createTaskNamed(std::string name, F&& f, Args&&... args) 
    -> TaskWrapper<typename std::result_of<F(Args...)>::type>{
    // std::tuple<TaskCookie<typename std::result_of<F(Args...)>::type>,taskptr> {
    using rt = typename std::result_of<F(Args...)>::type;
    auto task = new Task<rt(Args...)>(name,std::forward<F>(f),std::forward<Args>(args)...);

    TaskCookie tc(task->get_future());

    taskptr realTask = taskptr(reinterpret_cast<Task<void()>*>(task));

    return TaskWrapper(std::move(tc),std::move(realTask));


}

#define EXT_FUNC_NAME_STR_(N, ...) #N
#define EXT_FUNC_NAME_STR(args) EXT_FUNC_NAME_STR_ args
#define createTask(...) createTaskNamed(EXT_FUNC_NAME_STR((__VA_ARGS__)),__VA_ARGS__)