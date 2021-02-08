#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

class Weapon : public PowerUp
{
public:
    Weapon(std::string name, Vertex position, float damage) :
        PowerUp(std::move(name), std::move(position), PowerUpType::WEAPON),
        mDamage(damage)
    {}

private:
    float mDamage;
};

#endif // WEAPON_H

