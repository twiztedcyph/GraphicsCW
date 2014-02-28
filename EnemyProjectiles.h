#pragma once
#include "Bullet.h"
#include <vector>

class EnemyProjectiles
{
public:
	EnemyProjectiles();
	~EnemyProjectiles();

	void add(Bullet newBullet);
	void remove(double playerX, double playerY);
	int getSize();
	void drawAllBullets();
	void updataAllBullets(double deltaT);
	Bullet* getBullet(unsigned int index);
	bool canDel(Bullet b);
	std::vector<Bullet> getVector();
};

