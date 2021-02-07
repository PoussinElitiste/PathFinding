#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"

#include <stdio.h>

typedef std::vector<float> NodeDistances;

// Following Research, Dijkstra offer shortest solution for single-source path problem with non negative edge weight
bool FindPowerUp(PathNodes& path, PowerUp::PowerUpType puType, PathNode *start)
{
    /* Example:
    path.push_back(start);
    path.push_back(secondNode);
    path.push_back(endNode);
    return(true);*/

    // TODO:
    
    return(false); // No path found.
}

// For this example, all links are symmetric.
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
    if (!n1 || !n2)
    {
        printf("[ERROR] invalid node");
        return;
    }

    auto weight = n1->
    //NodeDistances
    n1->AddLink(n2);
    n2->AddLink(n1);
}

int main(int, char*[])
{
    typedef std::vector<std::unique_ptr<PowerUp>> UniquePowerUps;
    typedef std::vector<std::unique_ptr<PathNode>> UniquePathNodes;

    UniquePathNodes pathNodes;
    pathNodes.emplace_back(std::make_unique<PathNode>("Node0", std::move(Vertex(300, 60 , 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node1", std::move(Vertex(100, 60 , 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node2", std::move(Vertex(80 , 560, 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node3", std::move(Vertex(280, 650, 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node4", std::move(Vertex(300, 250, 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node5", std::move(Vertex(450, 400, 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node6", std::move(Vertex(450, 60 , 0))));
    pathNodes.emplace_back(std::make_unique<PathNode>("Node7", std::move(Vertex(450, 400, 0))));

    LinkNodes(pathNodes[1].get(), pathNodes[4].get());
    LinkNodes(pathNodes[0].get(), pathNodes[1].get());
    LinkNodes(pathNodes[0].get(), pathNodes[6].get());
    LinkNodes(pathNodes[0].get(), pathNodes[4].get());
    LinkNodes(pathNodes[7].get(), pathNodes[4].get());
    LinkNodes(pathNodes[7].get(), pathNodes[5].get());
    LinkNodes(pathNodes[2].get(), pathNodes[4].get());
    LinkNodes(pathNodes[2].get(), pathNodes[3].get());
    LinkNodes(pathNodes[3].get(), pathNodes[5].get());

    UniquePowerUps powerUps;

    powerUps.emplace_back(std::make_unique<Weapon>("Weapon0", std::move(Vertex(340, 670, 0))));
    pathNodes[3]->AddPowerUp(powerUps[0].get());    
    powerUps.emplace_back(std::make_unique<Weapon>("Weapon1", std::move(Vertex(500, 220, 0))));
    pathNodes[7]->AddPowerUp(powerUps[1].get());

    powerUps.emplace_back(std::make_unique<Health>("Health0", std::move(Vertex(490, 10, 0)), 5.f));
    pathNodes[6]->AddPowerUp(powerUps[2].get());
    powerUps.emplace_back(std::make_unique<Health>("Health1", std::move(Vertex(120, 20, 0)), 10.f));
    pathNodes[1]->AddPowerUp(powerUps[3].get());

    powerUps.emplace_back(std::make_unique<Armor>("Armour0", std::move(Vertex(500, 360, 0))));
    pathNodes[5]->AddPowerUp(powerUps[4].get());
    powerUps.emplace_back(std::make_unique<Armor>("Armour1", std::move(Vertex(180, 525, 0))));
    pathNodes[2]->AddPowerUp(powerUps[5].get());

    PathNodes path;

    if(!FindPowerUp(path, PowerUp::PowerUpType::WEAPON, pathNodes[4].get()))
    {
        printf("No path found: IMPOSSIBLE!\n");
    }
    else
    {
        printf("Path found: ");

        for (auto node : path)
        {
            printf("%s ", node->GetName().c_str());
        }

        printf("\n");
    }
       
    return 0;
}
