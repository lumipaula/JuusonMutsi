#include <iostream>

#include "loader.h"

#include "Display.h"
#include "framebuffer.h"


//Audio, video, input, etc 

void test(){
    std::cout << "Hello jöysäs mutsi sdl" << std::endl;
}


int main(void){
    test();

    Display d;

    d.loadWindow("JuusonMutsi",800,800);

    while(true){}


    return 0;
}