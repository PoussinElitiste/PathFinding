#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

class Armor : public PowerUp
{
public:
    Armor(std::string name, Vertex position, float hitPoint) :
        PowerUp(std::move(name), std::move(position), PowerUpType::ARMOUR),
        mHitPoint(hitPoint)
    {}

    ~Armor() = default;

    const char* GetClanTag() const
    {
        return mClanTag.c_str();
    }

    void SetClanTag(const char* n)
    {
        mClanTag = n;
    }

protected:
    std::string mClanTag;
    float mHitPoint;
};

#endif // ARMOUR_H

