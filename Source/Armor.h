#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

class Armor : public PowerUp
{
public:
    Armor(std::string name, Vertex position) :
        PowerUp(std::move(name), std::move(position), PowerUpType::ARMOUR)
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
};

#endif // ARMOUR_H

