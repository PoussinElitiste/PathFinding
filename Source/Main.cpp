#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"
#include "PathSection.h"

#include <stdio.h>
#include <algorithm>
#include <unordered_map>
#include <deque>

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
    std::vector<PathNode*> targetNodes;

    // Helpers
    auto isExploredNode = [&exploredNode](const PathNode* node) -> bool
    {
        return std::find(exploredNode.begin(), exploredNode.end(), node) != exploredNode.end();
    };

    auto containPowerUp = [puType](const PowerUps &puList) -> bool
    {
        return std::find_if(puList.begin(), puList.end(), [puType](const PowerUp *pu) -> bool{
            return pu->GetPowerUpType() == puType;
        }) != puList.end();
    };

    // initialize Path Resolver
    for (const auto &node: sPathNodes)
    {
        pathResolver.emplace(std::make_pair( node.get(), PathSection(node.get()) ));
        if (containPowerUp(node->GetPowerUps()))
        {
            targetNodes.push_back(node.get());
        }
    }

    // define start point
    auto currentNode = start;
    pathResolver.at(start).totalDistance = 0.;

    // feed Path Resolver
    while (currentNode && !isExploredNode(currentNode))
    {
        PathNode* closestNode = {};
        // Loop through attached nodes
        for (auto linkedNode : currentNode->GetLinks())
        {
            if (!isExploredNode(linkedNode))
            {
                auto& nextSection = pathResolver.at(linkedNode);
                double nextNodeWeight = currentNode->GetDistance(linkedNode);

                // Resolve total distance and update Path Resolver
                double totalDistance = pathResolver.at(currentNode).totalDistance + nextNodeWeight;
                if (totalDistance < nextSection.totalDistance)
                {
                    nextSection.totalDistance = totalDistance;
                    nextSection.parentSection = &pathResolver.at(currentNode);
                }

                // find next closest node
                if (!closestNode || nextNodeWeight < closestNode->GetDistance(currentNode) )
                {
                    closestNode = linkedNode;
                }
            }
        }
        
        // register has explored node
        exploredNode.push_back(currentNode);

        // adjustment to be sure all node are explored
        if (!closestNode && exploredNode.size() < pathResolver.size())
        {
            for (auto linkedNode : start->GetLinks())
            {
                if (!isExploredNode(linkedNode))
                {
                    double nextNodeWeight = start->GetDistance(linkedNode);
                    // find next closest node
                    if (!closestNode || nextNodeWeight < closestNode->GetDistance(start))
                    {
                        closestNode = linkedNode;
                    }
                }
            }
        }

        // set next node to explore
        currentNode = closestNode;
    }

    // find closest target
    PathNode* closestTarget = {};
    for (auto target :targetNodes)
    {
        if (!closestTarget || pathResolver.at(target).totalDistance < pathResolver.at(closestTarget).totalDistance)
        {
            closestTarget = target;
        }
    }
    
    std::deque<PathNode*> targetPath;
    if (closestTarget)
    {
        // travel path resolver from target to start node
        const PathSection *currentSection = &pathResolver.at(closestTarget);
        while (currentSection->parentSection)
        {
            targetPath.push_front(currentSection->targetNode);
            currentSection = currentSection->parentSection;
        }
    }

    path.push_back(start);
    for (auto node : targetPath)
        path.push_back(node);

    return path.size() > 1;
}

// For this example, all links are symmetric.
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
    if (!n1 || !n2)
    {
        printf("[ERROR] [LinkNodes] invalid node");
        return ;
    }

    Vertex direction = n1->GetVertex() - n2->GetVertex();
    double distance = direction.length();
    n1->AddLink(n2);
    n1->SetDistance(n2, distance);

    n2->AddLink(n1);
    n2->SetDistance(n1, distance);
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
