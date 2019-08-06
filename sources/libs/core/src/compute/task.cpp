#include "task.h"


std::ostream &operator <<(std::ostream &output, Task<void()> const& task){
    output << task.m_functionName;
    return output;
}