#pragma once
#include "level.h"
int Test();

class Enemy {
public:
	Enemy();
	void Move();
	void Update();
	float xPosition;
	float yPosition;
	bool spawned;
};

