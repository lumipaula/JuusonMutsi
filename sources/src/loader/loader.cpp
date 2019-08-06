#include <iostream>

#include "loader.h"

/* 

#include "Display.h"
#include "framebuffer.h"

*/
#include "workers.h"


//Audio, video, input, etc 




void test(){
    std::cout << "Hello jöysäs mutsi sdl" << std::endl;
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
    return b;
}


int main(void){
    //test();

    //auto fuck = createTask(test);

    //std::cout << fuck.get(); 

    

    ThreadPool tp(16);
    tp.enqueue(test);
    auto ret = tp.enqueue(test2);
    auto ret2 = tp.enqueue(test3, 5.4f, 3.0f);
    auto ret3 = tp.enqueue(test4,666);
    std::cout << ret.waitAndGet() << std::endl;
    std::cout << ret3.waitAndGet() << std::endl;
    std::cout << ret2.waitAndGet() << std::endl;

    

    //Display d;

    //d.loadWindow("JuusonMutsi",800,800);

    //while(true){}


    return 0;
}