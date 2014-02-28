#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include "EnemyProjectiles.h"
#include <vector>

using namespace::std;

std::vector<Bullet> enemyBullets;
EnemyProjectiles::EnemyProjectiles()
{
}


EnemyProjectiles::~EnemyProjectiles()
{
}

void EnemyProjectiles::add(Bullet newBullet)
{
	enemyBullets.push_back(newBullet);
}

void EnemyProjectiles::remove(double playerX, double playerY)
{

	//Add camera positions back....
	if (enemyBullets.size() > 0)
	{
		std::vector<Bullet>::iterator it = enemyBullets.begin();
		while (it != enemyBullets.end())
		{
			//cout << "test: " << it->destroyed << endl;
			if (it->destroyed == true || it->ttl <= 0)
			{
				it = enemyBullets.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

int EnemyProjectiles::getSize()
{
	return enemyBullets.size();
}

void EnemyProjectiles::drawAllBullets()
{
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i].drawBullet();
	}
}

void EnemyProjectiles::updataAllBullets(double deltaT)
{
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullets[i].updateBullet(deltaT);
	}
}

std::vector<Bullet> EnemyProjectiles::getVector()
{
	return enemyBullets;
}

Bullet* EnemyProjectiles::getBullet(unsigned int index)
{
	return &enemyBullets[index];
}


