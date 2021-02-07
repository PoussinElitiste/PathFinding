#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

class Weapon : public PowerUp
{
public:
    Weapon(std::string name, Vertex position) :
        PowerUp(std::move(name), std::move(position), PowerUpType::WEAPON)
    {}
};

#endif // WEAPON_H

