#include "level.h"

int level[] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,0,1,
1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,1,0,1,
1,0,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,1,
1,0,0,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1,0,1,
1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,
1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,0,1,1,
1,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
1,0,1,0,0,0,0,1,1,0,0,0,1,0,1,1,1,1,1,1,
1,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,
1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

};

NavigationNode* navNodes[300];
std::vector<NavigationNode*> openNodes;

std::vector<Coordinate> GetPath(Coordinate* start, Coordinate* end) {
    std::vector<Coordinate> path;

    OpenNode(start->x, start->y);

    while (openNodes.size() > 0) {
        NavigationNode* node = openNodes[0];// todo heuretic based
        OpenNeighbors(node->xPosition, node->yPosition);
        openNodes.
    }

    return path;
}


void InitalizeNavNodes() {
	
    int i = 0;
    for (size_t y = 0; y < 15; y++)
    {
        for (size_t x = 0; x < 20; x++)
        {
            NavigationNode* node = new NavigationNode();
            node->xPosition = x;
            node->yPosition = y;
            node->open = false;
            node->parent = NULL;
            node->heuretic = 0.0;
            navNodes[i] = node;

            i++;
        }
    }

}

void OpenNode(int x, int y) {

}

void OpenNeighbors(int x, int y) {

}



