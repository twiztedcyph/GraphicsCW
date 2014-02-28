#include "ExplosionList.h"
#include <iostream>


ExplosionList::ExplosionList()
{
}

ExplosionList::~ExplosionList()
{
}

void ExplosionList::addExplosion(Explosion& explosion)
{
	this->explosionList.push_back(explosion);
	std::cout << "ADDED EXPLOSION: " << explosionList.size() << std::endl;
}

void ExplosionList::updateAllExplosions(double deltaT)
{
	for (unsigned int i = 0; explosionList.size() > 0 && i < explosionList.size(); i++)
	{
		explosionList[i].updateExplosion(deltaT);
	}
}

void ExplosionList::drawAllExplosions()
{
	for (unsigned int i = 0; explosionList.size() > 0 && i < explosionList.size(); i++)
	{
		explosionList[i].drawExplosion();
	}
}

void ExplosionList::removeExplosions()
{
	if (explosionList.size() > 0)
	{
		std::vector<Explosion>::iterator it = explosionList.begin();
		while (it != explosionList.end())
		{
			//cout << "test: " << it->destroyed << endl;
			if ((*it).finished)
			{
				it = explosionList.erase(it);
				std::cout << "REMOVED EXPLOSION" << std::endl;
			}
			else
			{
				++it;
			}
		}
	}
}


