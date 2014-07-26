#pragma once
#include "PlayerShip.h"

class StarField
{
private:
	int smallCount, mediumCount, largeCount;
	PlayerShip* playerRef;
public:
	StarField(int sml, int med, int lrg, PlayerShip* player);
	StarField();
	~StarField();

	void initialise();
	void initialise(double xPos, double yPos);
	void move(double deltaT);
	void clear();
	void updateAll(double camY, double camX);
	void drawAll();
	int size();
};

