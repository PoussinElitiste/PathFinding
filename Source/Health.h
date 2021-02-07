#ifndef HEALTH_H
#define HEALTH_H

#include "PowerUp.h"

class Health : public PowerUp
{
public:
    Health(std::string name, Vertex position, float healing) : 
        PowerUp(std::move(name), std::move(position), PowerUpType::HEALTH), 
        mHealing(healing)
    {}
    
protected:
    float mHealing;
};

#endif // HEALTH_H

