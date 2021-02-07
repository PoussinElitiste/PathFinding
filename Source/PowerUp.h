#ifndef POWER_UP_H
#define POWER_UP_H

#include "Vertex.h"
#include <string>

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

    PowerUp(std::string name, Vertex position, PowerUpType pType = PowerUpType::INVALID) : 
        mType(pType), 
        mPosition(std::move(position)), 
        mName(std::move(name))
    {}

    virtual ~PowerUp() = default;

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
    const std::string mName;
};

#endif // POWER_UP_H
