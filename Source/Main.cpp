#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"
#include "PathSection.h"

#include <stdio.h>
#include <algorithm>
#include <unordered_map>

typedef std::vector<std::unique_ptr<PowerUp>> UniquePowerUps;
typedef std::unique_ptr<PathNode> PathNodePtr;
typedef std::vector<PathNodePtr> UniquePathNodes;
typedef std::unordered_map<PathNode*, PathSection> ResolutionPaths;

static UniquePathNodes sPathNodes;
static UniquePowerUps sPowerUps;

bool NodeContainPoWerUp(const PowerUps& puList, const PowerUp::PowerUpType puType)
{
    auto IsPowerUp = [puType](const PowerUp* pu) -> bool
    {
        return pu->GetPowerUpType() == puType;
    };

    return std::find_if(puList.begin(), puList.end(), IsPowerUp) != puList.end();
}

// Following Research, Dijkstra offer shortest solution for single-source path problem with non negative edge weight
bool FindPowerUp(PathNodes& path,const PowerUp::PowerUpType puType, PathNode *start)
{
    if (!start)
    {
        printf("[ERROR] [FindPowerUp] invalid node");
        return false;
    }

    ResolutionPaths pathResolver;
    std::vector<PathNode*> exploredNode;
    // init Path Resolver
    for (const auto &node: sPathNodes)
    {
        pathResolver[node.get()] = {};
    }

    // define start point
    auto currentNode = start;
    exploredNode.push_back(start);
    pathResolver[start].totalDistance = 0.;

    //while (!currentNode->IsExplored())
    //{
    //    currentNode->Explored();
    //    for (auto nextNode : currentNode->GetLinks())
    //    {
    //        if (nextNode)
    //        {
    //        }
    //    }
    //}

    //path.push_back(secondNode);
    //path.push_back(endNode);
    path.push_back(start);
    return path.size() > 1;
}

bool GetClosestNode(const PowerUps& puList, const PowerUp::PowerUpType puType)
{
    return false;
}


// For this example, all links are symmetric.
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
    if (!n1 || !n2)
    {
        printf("[ERROR] invalid node");
        return ;
    }

    Vertex distance = n1->GetVertex() - n2->GetVertex();
    double weight = distance.length();
    n1->AddLink(n2, weight);
    n2->AddLink(n1, weight);
}

int main(int, char*[])
{
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node0", std::move(Vertex(300, 60 , 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node1", std::move(Vertex(100, 60 , 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node2", std::move(Vertex(80 , 560, 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node3", std::move(Vertex(280, 650, 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node4", std::move(Vertex(300, 250, 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node5", std::move(Vertex(450, 400, 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node6", std::move(Vertex(450, 60 , 0))));
    sPathNodes.emplace_back(std::make_unique<PathNode>("Node7", std::move(Vertex(450, 400, 0))));

    LinkNodes(sPathNodes[1].get(), sPathNodes[4].get());
    LinkNodes(sPathNodes[0].get(), sPathNodes[1].get());
    LinkNodes(sPathNodes[0].get(), sPathNodes[6].get());
    LinkNodes(sPathNodes[0].get(), sPathNodes[4].get());
    LinkNodes(sPathNodes[7].get(), sPathNodes[4].get());
    LinkNodes(sPathNodes[7].get(), sPathNodes[5].get());
    LinkNodes(sPathNodes[2].get(), sPathNodes[4].get());
    LinkNodes(sPathNodes[2].get(), sPathNodes[3].get());
    LinkNodes(sPathNodes[3].get(), sPathNodes[5].get());

    sPowerUps.emplace_back(std::make_unique<Weapon>("Weapon0", std::move(Vertex(340, 670, 0))));
    sPathNodes[3]->AddPowerUp(sPowerUps[0].get());    
    sPowerUps.emplace_back(std::make_unique<Weapon>("Weapon1", std::move(Vertex(500, 220, 0))));
    sPathNodes[7]->AddPowerUp(sPowerUps[1].get());

    sPowerUps.emplace_back(std::make_unique<Health>("Health0", std::move(Vertex(490, 10, 0)), 5.f));
    sPathNodes[6]->AddPowerUp(sPowerUps[2].get());
    sPowerUps.emplace_back(std::make_unique<Health>("Health1", std::move(Vertex(120, 20, 0)), 10.f));
    sPathNodes[1]->AddPowerUp(sPowerUps[3].get());

    sPowerUps.emplace_back(std::make_unique<Armor>("Armour0", std::move(Vertex(500, 360, 0))));
    sPathNodes[5]->AddPowerUp(sPowerUps[4].get());
    sPowerUps.emplace_back(std::make_unique<Armor>("Armour1", std::move(Vertex(180, 525, 0))));
    sPathNodes[2]->AddPowerUp(sPowerUps[5].get());

    PathNodes path;

    if (!FindPowerUp(path, PowerUp::PowerUpType::WEAPON, sPathNodes[4].get()))
    {
        printf("No path found: IMPOSSIBLE!\n");
    }
    else
    {
        printf("Path found: ");

        for (auto node : path)
        {
            printf("%s ", node->GetName());
        }

        printf("\n");
    }
       
    sPathNodes.clear();
    sPowerUps.clear();

    return 0;
}
