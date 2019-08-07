#include <iostream>

#include "loader.h"

/* 

#include "Display.h"
#include "framebuffer.h"

*/
#include "workers.h"
#include "task.h"

//Audio, video, input, etc 

std::unique_ptr<Task<void()>> callbackTest;


void test(){
    static int asd = 0;
    asd++;
    std::cout << "This is a test " << asd << std::endl;
}

int test2(){
    static int asd = 609;
    asd++;
    return asd;
}

float test3(float a, float b){
    return a*b;
}

int test4(int b){
    std::cout << "This is a test " << b << std::endl;
    return b;
}

std::string test5(){
    return "Perseripuli";
}

std::string test6(std::string a,std::string b){
    return a + b;
}


int main(void){
    //test();

    //auto fuck = createTask(test);

    //std::cout << fuck.get(); 

    ThreadPool tp(16);




    auto t = createTask(test);

    auto task = std::move(std::get<1>(t));

    task->setCallback(true);
    task->setCallbackFun([](std::unique_ptr<Task<void()>> task){
        callbackTest = std::move(task);
    });

    task->execute();
    task->reset();
    task->m_callbackFun(std::move(task));

    callbackTest->execute();

    std::list<taskptr> tasklist;

    for(int i=0;i<5;i++){
        tasklist.emplace_back(std::move(std::get<1>(createTask(test4,i))));
        tasklist.back()->setCallback(true);
        tasklist.back()->setCallbackFun([&tasklist](taskptr tusk){
            tasklist.push_back(std::move(tusk));
        });
    }

    tp.enqueueList(tasklist);
    //cookie.wait();

    //tp.enqueueList(tasklist);


    


    //Display d;

    //d.loadWindow("JuusonMutsi",800,800);

    //while(true){}


    return 0;
}