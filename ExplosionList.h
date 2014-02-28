#pragma once
#include <vector>
#include "Explosion.h"

class ExplosionList
{
private:
	std::vector<Explosion> explosionList;
public:
	ExplosionList();
	~ExplosionList();

	void addExplosion(Explosion& explosion);
	void updateAllExplosions(double deltaT);
	void drawAllExplosions();
	void removeExplosions();
};

