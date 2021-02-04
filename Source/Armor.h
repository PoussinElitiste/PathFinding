#ifndef ARMOUR_H
#define ARMOUR_H

#include "PowerUp.h"

class Armor : public PowerUp
{
public:
    Armor(const char* name, const Vertex& position) :
        PowerUp(name, position, PowerUpType::ARMOUR), mClanTag(NULL)
    {}

    ~Armor()
    {
        delete mClanTag;
    }

    const char* GetClanTag() const
    {
        return mClanTag;
    }

    void SetClanTag(char* n)
    {
        mClanTag = n;
    }

protected:
    char* mClanTag;
};

#endif // ARMOUR_H

