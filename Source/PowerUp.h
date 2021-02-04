#ifndef POWER_UP_H
#define POWER_UP_H

#include "Vertex.h"

class PowerUp
{
public:
    enum class PowerUpType
    {
        INVALID = -1,
        WEAPON,
        ARMOUR,
        HEALTH
    };

    PowerUp(const char* name, Vertex position, PowerUpType pType = PowerUpType::INVALID):
        mType(pType), mPosition(std::move(position)), mName(name)
    {    }

    ~PowerUp()
    {
        delete mName;
    }   

    PowerUpType GetPowerUpType() const
    {
        return mType;
    };

    const Vertex& GetPosition() const
    {
        return mPosition;
    }

protected:
    Vertex      mPosition;
    PowerUpType mType;
    const char* mName;
};

#endif // POWER_UP_H
