#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"
#include <memory>
#include <vector>

class PathNode;
typedef std::vector<PathNode*> PathNodes;

class PowerUp;
typedef std::vector<PowerUp*> PowerUps;

class PathNode
{
public:
    PathNode(const char* name, Vertex position) :
        mPosition(std::move(position)), mName(name)
    {}
    
    ~PathNode() = default;

    void AddLink(PathNode *pathNode)
    {
        mLinks.push_back(pathNode);
    }
    
    void RemoveLink(PathNode *pathNode)
    {
        PathNodes::iterator i = std::find(mLinks.begin(), mLinks.end(), pathNode);
        mLinks.erase(i);
    }

    void AddPowerUp(PowerUp *powerUp)
    {
        mPowerUps.push_back(powerUp);
    }
    
    void RemovePowerUp(PowerUp *powerUp)
    {
        PowerUps::iterator it = std::find(mPowerUps.begin(), mPowerUps.end(), powerUp);
        mPowerUps.erase(it);
    }

    const char* GetName() const
    {
        return mName;
    }

    const PathNodes& GetLinks() const
    {
        return mLinks;
    }

    const PowerUps& GetPowerUps() const
    {
        return mPowerUps; 
    }

protected:
    Vertex      mPosition;
    const char* mName;

    PathNodes   mLinks;
    PowerUps    mPowerUps;
};

#endif // PATH_NODE_H
