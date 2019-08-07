#pragma once

#include "jmtime.h"
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

struct Event{
    //We don't want to store unique_ptr in here
    //Id is used to fetch the task from hashmap
    int m_id;

    bool m_recurring;
    int m_epoch;
    timeStampMillis m_triggerTime;
    
    bool operator()(const Event &left, const Event &right){
        return left.m_triggerTime > right.m_triggerTime;
    }

};

class EventHandler{
private:
    std::priority_queue<Event,std::vector<Event>,Event> m_eventQueue;
    std::unordered_map<int,Task<void()>> m_triggeredTasks;
    std::mutex m_mutex;
    std::mutex m_conditionMutex;
    std::condition_variable m_cv;
    bool m_running;
public:
    EventHandler();
    ~EventHandler();

    void addEvent(Task<void()>, int millis);
    void addEvent(Task<void()>, int millis, bool recurring, int epoch);

    void addEvent(Task<void()>, timeStampMillis millis);
    void addEvent(Task<void()>, timeStampMillis millis, bool recurring, int epoch);

    void stopRecurringEvent(int id);

    void eventLoop();

};