#pragma once
#include <vector>
class NavigationNode {
public:
	int xPosition;
	int yPosition;
	bool open;
	bool closed;
	NavigationNode* parent;
	float heuretic;

};

class Coordinate {
public:
	int x;
	int y;
};

extern int level[];
NavigationNode* navNodes[];

#ifndef METHODS
#define METHODS

std::vector<int[]> GetAPath(int startX, int startY, int endX, int endY);

void InitializeNavNodes();

void OpenNode(int x, int y);

void OpenNeighbours(int x, int y);

bool IsBlocked(int x, int y);

NavigationNode* GetNode(int x, int y);

#endif


