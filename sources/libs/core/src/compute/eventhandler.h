#pragma once

#include "jmtime.h"

struct TimedTrigger{
    //We don't want to store unique_ptr in here
    //Id is used to fetch the task from hashmap
    int m_id;

    bool m_recurring;
    int m_epoch;
    timeStampMillis m_triggerTime;
    
    bool operator()(const TimedTrigger &left, const TimedTrigger &right){
        
    }

};

class EventHandler{

};