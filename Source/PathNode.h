#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>

class PathNode;
typedef std::vector<PathNode*> PathNodes;
typedef std::unordered_map<PathNode*, double> NodeDistances;

class PowerUp;
typedef std::vector<PowerUp*> PowerUps;

class PathNode
{
public:
    PathNode(std::string name, Vertex position) : 
        mPosition(std::move(position)), 
        mName(std::move(name))
    {}
    
    ~PathNode() = default;

    void AddLink(PathNode *pathNode, double weight)
    {
        if (!pathNode)
        {
            printf("[ERROR] [AddLink] Invalid node");
            return;
        }
       
        mDistances.emplace(pathNode, weight);
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
        return mName.c_str();
    }

    const Vertex& GetVertex() const
    {
        return mPosition;
    }

    const PathNodes& GetLinks() const
    {
        return mLinks;
    }

    double GetDistance(PathNode* pathNode) const
    {
        if (mDistances.count(pathNode) > 0)
        {
            return mDistances.at(pathNode);
        }
        return std::numeric_limits<double>::max();
    }

    const PowerUps& GetPowerUps() const
    {
        return mPowerUps; 
    }

protected:
    Vertex              mPosition;
    const std::string   mName;

    PathNodes           mLinks;
    NodeDistances       mDistances;
    PowerUps            mPowerUps;
};

#endif // PATH_NODE_H
