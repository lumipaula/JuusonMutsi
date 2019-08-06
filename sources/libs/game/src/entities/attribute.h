#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "effect.h"

/*
Sense of time
HP
*/

std::string attributeIdToString(int id);

int attributeStringToId(const std::string &str);


struct AttributeModifier{

};



struct Attribute{

    int m_uid;
    int m_value;
    int m_modifier;
    std::vector<AttributeModifier> m_modifiers;

};