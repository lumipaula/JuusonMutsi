#pragma once
#include <map>
#include <unordered_map>
#include <string>




struct EntityCreateInfo{

};

class Entity{
private:
    std::unordered_map<int,int> m_attributes;

public:
    Entity(EntityCreateInfo ect);


    virtual void passTurn();

};