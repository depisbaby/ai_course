#pragma once
#include <vector>
class NavigationNode {
public:
	int xPosition;
	int yPosition;
	bool open;
	NavigationNode* parent;
	float heuretic;

};

extern int level[];
NavigationNode* navNodes[];

std::vector<int[]> GetAPath(int startX, int startY, int endX, int endY);

void InitializeNavNodes();

void OpenNode(int x, int y);

void OpenNeighbours(int x, int y);


