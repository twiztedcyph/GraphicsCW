#pragma once
#include "Bullet.h"
#include <vector>

class PlayerProjectiles
{
private:
	//Ask about this....
	//std::vector<Bullet> bullets;
public:
	PlayerProjectiles();

	void add(Bullet newBullet);

	void remove(double camY);

	int getSize();

	void drawAllBullets();

	void updateAllBullets(double deltaT);

	Bullet* getBullet(unsigned int index);

	bool canDel(Bullet b);

	std::vector<Bullet> getVector();
};

