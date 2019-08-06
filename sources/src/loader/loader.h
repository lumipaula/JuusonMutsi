#pragma once
#include <functional>
#include <future>

template<class T, class... Args>
class Ta : public std::packaged_task<typename std::result_of<T(Args...)>::type(Args...)>{
private:
public:

    Ta(T&& t, Args&&... args)   :
        std::packaged_task<typename std::result_of<T(Args...)>::type(Args...)>
                (std::bind(std::forward<T>(t),std::forward<Args>(args)...)){
    }

};


template<class F,class... Args>
auto createTask(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>{

    

    auto vittuPerse = Ta<F,Args...>(std::forward<F>(f),std::forward<Args>(args)...);

    (vittuPerse)();


    return vittuPerse.get_future();
}



void test();