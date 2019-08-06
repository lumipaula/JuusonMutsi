#pragma once
#include <memory>
#include <future>
#include <functional>
#include <iostream>



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



};


template<typename RT>
class Task : public std::packaged_task<RT>{
private:
public:

    template<class F, class... Args>
    Task(F&& f, Args&&... args)   :
        std::packaged_task<RT>
                (std::bind(std::forward<F>(f),std::forward<Args>(args)...))
        //m_cookie(this->get_future())
        {
    }

    bool execute(){
        (*this)();
    }


};


