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

bool IsBlocked(int x, int y) {

    int i = x + y * 20;
    if (level[i] == 1) {
        return true;
    }
    else {
        return false;
    }
}

void OpenNode(int x, int y, NavigationNode* parent) {
    NavigationNode* node = GetNode(x, y);

    if (node->open||node->closed)
        return;

    node->open = true;
    node->parent = parent;
    openNodes.push_back(node);
}


NavigationNode* GetNode(int x, int y) {
    int i = x + y * 20;
    return navNodes[i];
}

void OpenNeighbors(int x, int y, NavigationNode* parent) {
    
    if (!IsBlocked(x, y+1)) {
        OpenNode(x, y + 1,parent);
    }

    if (!IsBlocked(x+1, y)) {
        OpenNode(x, y + 1,parent);
    }

    if (!IsBlocked(x, y-1)) {
        OpenNode(x, y + 1,parent);
    }

    if (!IsBlocked(x-1, y)) {
        OpenNode(x, y + 1,parent);
    }
}

std::vector<Coordinate> GetPath(Coordinate* start, Coordinate* end) {
    std::vector<Coordinate> path;

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

    }

    NavigationNode* pathHead = GetNode(end->x,end->y);
    while (true) 
    {
        Coordinate pathHeadCord;
        pathHeadCord.x = pathHead->xPosition;
        pathHeadCord.y = pathHead->yPosition;
        path.insert(path.begin(), pathHeadCord);

        pathHead = pathHead->parent;

        if pathHead ==
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
            node->closed = false;
            node->parent = NULL;
            node->heuretic = 0.0;
            navNodes[i] = node;

            i++;
        }
    }

}




