#include "jmtime.h"



const std::vector<std::string> weekDays {
    "JM_STR_MONDAY",
    "JM_STR_TUESDAY",
    "JM_STR_WEDNESDAY",
    "JM_STR_THURSDAY",
    "JM_STR_FRIDAY",
    "JM_STR_SATURDAY",
    "JM_STR_SUNDAY"
};


void Turn::addTask(std::unique_ptr<Task<void()>> task){

}

void Turn::nextTurn(){
    m_current++;
    for(auto &t : m_tasks){

    }
}


Clock::Clock(){

}




int UnitOfTime::passTime(int count){

}

