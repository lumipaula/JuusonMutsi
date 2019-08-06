#pragma once

#include "jmlog.h"

//

struct Effect{
    virtual void apply(){

    }
};

struct Explosion : public Effect{

};

struct Burn : public Effect{

};

struct AttributeEffect : public Effect{

};


class Effectable{
public:
    virtual void applyEffect(Effect e);

};