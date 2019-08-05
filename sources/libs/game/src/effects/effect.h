#pragma once



//

class Effect{
    virtual void apply();
};

class Explosion : public Effect{

};

class Burn : public Effect{

};


class Effectable{
public:
    virtual void applyEffect(Effect e);

};