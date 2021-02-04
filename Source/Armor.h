#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

class Armor : public PowerUp
{
public:
    Armor(const char* name, Vertex position) :
        PowerUp(name, std::move(position), PowerUpType::ARMOUR), mClanTag(NULL)
    {}

    ~Armor()
    {
        delete[] mClanTag;
    }

    const char* GetClanTag() const
    {
        return mClanTag;
    }

    void SetClanTag(const char* n)
    {
        mClanTag = n;
    }

protected:
    const char* mClanTag;
};

#endif // ARMOUR_H

