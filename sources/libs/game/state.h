#pragma once

#include <list>
#include <string>


class GameState{
private:

public:
    //Default new game constructor
    GameState();

    //Load state from file
    GameState(std::string filename);

    bool save(std::string filename);
    bool load(std::string filename);

};