#include "level.h"
#include <iostream>
#include <random>

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

int levelWidth = 20;
int levelHeight = 15;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(21, 299);

NavigationNode* navNodes[300];
std::vector<NavigationNode*> openNodes;

bool IsBlocked(int x, int y) {

    int i = x + y * levelWidth;
    if (level[i] == 1) {
        return true;
    }
    else {
        return false;
    }
}

void OpenNode(int x, int y, NavigationNode* parent) {
    NavigationNode* node = GetNode(x, y);

    if (node == NULL || node->open || node->closed)
        return;

    node->open = true;
    node->parent = parent;
    openNodes.push_back(node);
}


NavigationNode* GetNode(int x, int y) {
    if (x > levelWidth-1 || x < 0) {
        return NULL;
    }

    if (y > levelHeight-1 || y < 0) {
        return NULL;
    }

    int i = x + y * levelWidth;
    return navNodes[i];
}

void OpenNeighbors(int x, int y, NavigationNode* parent) {
    
    if (!IsBlocked(x, y+1)) {
        OpenNode(x, y+1,parent);
    }

    if (!IsBlocked(x+1, y)) {
        OpenNode(x+1, y,parent);
    }

    if (!IsBlocked(x, y-1)) {
        OpenNode(x, y-1,parent);
    }

    if (!IsBlocked(x-1, y)) {
        OpenNode(x-1, y,parent);
    }
}

std::vector<Coordinate> GetPath(Coordinate* start, Coordinate* end) {
    std::vector<Coordinate> path;
    std::cout << "Got path from [" << start->x << "," << start->y << "] to [" << end->x << "," << end->y << "]\n";
    OpenNode(start->x, start->y,NULL);

    while (openNodes.size() > 0) {
        int index = 0;// todo heuretic based
        NavigationNode* node = openNodes[index];

        if (node->xPosition == end->x && node->yPosition == end->y) {
            break;
        }

        node->open = false;
        node->closed = true;

        OpenNeighbors(node->xPosition, node->yPosition,node);
        
        if (index < openNodes.size()) {
            openNodes.erase(openNodes.begin() + index);
        }

        ///std::cout << node->xPosition << ", " << node->yPosition << "\n";
    }

    NavigationNode* pathHead = GetNode(end->x,end->y);
    Coordinate pathHeadCord;
    while (true) 
    {
        pathHeadCord.x = pathHead->xPosition;
        pathHeadCord.y = pathHead->yPosition;

        path.insert(path.begin(), pathHeadCord);

        if (pathHead->parent != NULL) {

            pathHead = pathHead->parent;
        }
        else 
        {
            break;
        }
    }
    //std::cout << path.size();

    for (size_t i = 0; i < 300; i++)
    {
        navNodes[i]->closed = false;
        navNodes[i]->open = false;
    }

    return path;
}

std::vector<Coordinate> GetRandomPath(Coordinate* start) {
    int rnd;
    while (true)
    {
        rnd = distrib(gen);
        if (level[rnd] == 0) {
            break;
        }
    }

    NavigationNode* node = navNodes[rnd];

    Coordinate end;
    end.x = node->xPosition;
    end.y = node->yPosition;

    return GetPath(start, &end);
}

void InitializeNavNodes() {
	
    int i = 0;
    for (size_t y = 0; y < levelHeight; y++)
    {
        for (size_t x = 0; x < levelWidth; x++)
        {
            NavigationNode* node = new NavigationNode();
            node->xPosition = x;
            node->yPosition = y;
            node->open = false;
            node->closed = false;
            node->parent = NULL;
            node->heuretic = 0.0;
            navNodes[i] = node;

            i++;
        }
    }

}




