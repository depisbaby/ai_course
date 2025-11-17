#pragma once
#include "level.h"

class Enemy {
public:
	Enemy();
	void Move(float, float);
	void Update();
	void GetNewPath();
	float GetDistanceTo(float, float);
	float xPosition;
	float yPosition;
	int xNextWayPoint;
	int yNextWayPoint;
	float speed;
	bool spawned;
	int pathHead;
	std::vector<Coordinate> path;
};

