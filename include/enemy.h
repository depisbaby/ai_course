#ifndef ENEMY_H
#define ENEMY_H
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

class NavigationNode {
public:
	int xPosition;
	int yPosition;
	bool open;

};

#endif