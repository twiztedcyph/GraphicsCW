#pragma once
#include <vector>
#include "Collectable.h"

class CollectableList
{
public:
	std::vector<Collectable> collectableList;

	CollectableList();
	~CollectableList();

	void addCollectable(Collectable& collectable);
	void updateAllCollectables(double deltaT);
	void drawAllCollectables();
	void removeCollectable();
	Collectable* getCollectable(int index);
	int getSize();
};

