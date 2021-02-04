#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"

#include <stdio.h>

bool FindPowerUp(PathNodes& path, PowerUp::PowerUpType puType, PathNode *start)
{
    /* Example:
    path.push_back(start);
    path.push_back(secondNode);
    path.push_back(endNode);
    return(true);
    */
    
    return(false); // No path found.
}

// For this example, all links are symmetric.
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
    n1->AddLink(n2);
    n2->AddLink(n1);
}

int main(int, char*[])
{
    PathNodes pathNodes{
        new PathNode("Node0", Vertex(300, 60, 0)),
        new PathNode("Node1", Vertex(100, 60, 0)),
        new PathNode("Node2", Vertex(80, 560, 0)),
        new PathNode("Node3", Vertex(280, 650, 0)),
        new PathNode("Node4", Vertex(300, 250, 0)),
        new PathNode("Node5", Vertex(450, 400, 0)),
        new PathNode("Node6", Vertex(450, 60, 0)),
        new PathNode("Node7", Vertex(450, 400, 0))
    };

    LinkNodes(pathNodes[1], pathNodes[4]);
    LinkNodes(pathNodes[0], pathNodes[1]);
    LinkNodes(pathNodes[0], pathNodes[6]);
    LinkNodes(pathNodes[0], pathNodes[4]);
    LinkNodes(pathNodes[7], pathNodes[4]);
    LinkNodes(pathNodes[7], pathNodes[5]);
    LinkNodes(pathNodes[2], pathNodes[4]);
    LinkNodes(pathNodes[2], pathNodes[3]);
    LinkNodes(pathNodes[3], pathNodes[5]);

    PowerUps powerUps;

    powerUps.push_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
    pathNodes[3]->AddPowerUp(powerUps[0]);    
    powerUps.push_back(new Weapon("Weapon1", Vertex(500, 220, 0)));
    pathNodes[7]->AddPowerUp(powerUps[1]);    

    powerUps.push_back(new Health("Health0", Vertex(490, 10, 0), 5.f));
    pathNodes[6]->AddPowerUp(powerUps[2]);    
    powerUps.push_back(new Health("Health1", Vertex(120, 20, 0), 10.f));
    pathNodes[1]->AddPowerUp(powerUps[3]);    

    powerUps.push_back(new Armor("Armour0", Vertex(500, 360, 0)));
    pathNodes[5]->AddPowerUp(powerUps[4]);    
    powerUps.push_back(new Armor("Armour1", Vertex(180, 525, 0)));
    pathNodes[2]->AddPowerUp(powerUps[5]);    

    PathNodes path;

    if(!FindPowerUp(path, PowerUp::PowerUpType::WEAPON, pathNodes[4]))
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
       
    return 0;
}
