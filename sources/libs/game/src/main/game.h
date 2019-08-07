#pragma once

#include "state.h"
#include "commands.h"
#include "workers.h"
#include "task.h"
#include "eventhandler.h"


class Game{
private:
    ThreadPool m_threadpool;
    EventHandler m_eventhandler;
public:
    Game();


    bool mainLoop();

};