#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include "PlayerProjectiles.h"
#include <vector>

using namespace::std;

std::vector<Bullet> bullets;

PlayerProjectiles::PlayerProjectiles()
{
}

void PlayerProjectiles::add(Bullet bullet)
{
	bullets.push_back(bullet);	
}

int PlayerProjectiles::getSize()
{
	return bullets.size();
}

void PlayerProjectiles::remove(double camY)
{
	if (bullets.size() > 0)
	{
		std::vector<Bullet>::iterator it = bullets.begin();
		while (it != bullets.end())
		{
			//cout << "test: " << it->destroyed << endl;
			if ((*it).ttl <= 0 || it->destroyed == true)
			{
				it = bullets.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void PlayerProjectiles::drawAllBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].drawBullet();
	}
}

void PlayerProjectiles::updateAllBullets(double deltaT)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].updateBullet(deltaT);
	}
}

std::vector<Bullet> PlayerProjectiles::getVector()
{
	return bullets;
}

Bullet* PlayerProjectiles::getBullet(unsigned int index)
{
	return &bullets[index];
}