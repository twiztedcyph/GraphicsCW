#include "CollectableList.h"
#include <iostream>

CollectableList::CollectableList()
{
	oldSize = 0;
}


CollectableList::~CollectableList()
{
}

int CollectableList::getSize()
{
	return this->collectableList.size();
}

Collectable* CollectableList::getCollectable(int index)
{
	return &collectableList[index];
}

void CollectableList::addCollectable(Collectable& collectable)
{
	collectableList.push_back(collectable);
}

void CollectableList::updateAllCollectables(double deltaT)
{
	for (unsigned int i = 0; collectableList.size() > 0 && i < collectableList.size(); i++)
	{
		collectableList[i].updateCollectable(deltaT);
	}
}

void CollectableList::drawAllCollectables()
{
	for (unsigned int i = 0; collectableList.size() > 0 && i < collectableList.size(); i++)
	{
		collectableList[i].drawCollectable();
	}
}

void CollectableList::removeCollectable()
{
	if (collectableList.size() > 0)
	{
		std::vector<Collectable>::iterator it = collectableList.begin();
		while (it != collectableList.end())
		{
			//cout << "test: " << it->destroyed << endl;
			if ((*it).collected)
			{
				it = collectableList.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}