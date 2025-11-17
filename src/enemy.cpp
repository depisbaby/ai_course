#include "enemy.h"
#include <cmath> 
#include <iostream>

Enemy::Enemy() = default;

void Enemy::Move(float xTarget, float yTarget) {
	float xDir = xTarget - xPosition;
	float yDir = yTarget - yPosition;

	float len = std::sqrt(xDir * xDir + yDir * yDir);
	if (len == 0) len = 0.1;
	float xNorm = xDir / len;
	float yNorm = yDir / len;

	xPosition = xPosition + xNorm;
	yPosition = yPosition + yNorm;
}

void Enemy::Update() {

	Move(path[pathHead].x * 32, path[pathHead].y * 32);

	if (GetDistanceTo(path[pathHead].x*32, path[pathHead].y*32) < 2) {
		pathHead++;
	}

	if (pathHead == path.size()) {
		GetNewPath();
	}
	//std::cout << xPosition << ", " << yPosition << "\n";
}

void Enemy::GetNewPath() {
	
	path.clear();

	Coordinate start;
	start.x = xPosition / 32;
	start.y = yPosition / 32;

	path = GetRandomPath(&start);
	pathHead = 0;

}

float Enemy::GetDistanceTo(float xTarget, float yTarget) {
	float xDir = xTarget - xPosition;
	float yDir = yTarget - yPosition;

	return std::sqrt(xDir * xDir + yDir * yDir);
}


