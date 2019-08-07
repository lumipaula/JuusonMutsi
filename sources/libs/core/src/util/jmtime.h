#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <list>
#include "task.h"

template<typename RT>
class Task;

using namespace std::chrono;

using timeStampMicros = time_point<steady_clock,microseconds>;
using timeStampMillis = time_point<steady_clock,milliseconds>;
using timeStampSeconds = time_point<steady_clock,seconds>;



extern const std::vector<std::string> weekDays;


//Game is turn based
class Turn{
private:
    int m_current;
    //These are completed after every turn;
    std::list<std::unique_ptr<Task<void()>>> m_tasks;
public:
    void addTask(std::unique_ptr<Task<void()>> task);

    void doTasks();

    void nextTurn();
} gameTurn;






struct UnitOfTime{
    int m_count;
    int m_limit;
    virtual int passTime(int count);

    UnitOfTime(int count, int limit);
};



//Because for some reason months are stoopid and not logical and don't have the same number of days
struct Day : public UnitOfTime{



};

//Keep track of dates

class Clock{
private:
    //from smallest to biggest
    std::list<UnitOfTime> m_time;
    timeStampSeconds m_timeChrono;
public:
    Clock();
    Clock(int sec, int min, int h, int d, int mon, int y);
    Clock(timeStampSeconds tss);

    void passTime(int count);

    void chronoToCust();
    void custToChrono();


} realWorldClock, gameWorldClock;





