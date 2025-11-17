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
extern int levelHeight;
extern int levelWidth;
NavigationNode* navNodes[];

#ifndef METHODS
#define METHODS

void OpenNode(int x, int y);

void OpenNeighbours(int x, int y);

bool IsBlocked(int x, int y);

NavigationNode* GetNode(int x, int y);

std::vector<Coordinate> GetPath(Coordinate* start, Coordinate* end);
std::vector<Coordinate> GetRandomPath(Coordinate* start);

void InitializeNavNodes();

#endif


