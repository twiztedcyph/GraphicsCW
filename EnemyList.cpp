#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "enemyList.h"
#include "Collision.h"
#include <vector>
#include <iostream>
#include "RandomGen.h"
#include "PlayerProjectiles.h"
#include "EnemyProjectiles.h"
#include "Explosion.h"

EnemyList::EnemyList()
{
}


EnemyList::~EnemyList()
{
}

int EnemyList::getSize()
{
	return enemyList.size();
}

void EnemyList::spawnNewRandom(double playerX, double playerY, GLuint* enemyTextureID)
{
	double enemyX = playerX + RandomGen().getRand(20, -20);
	double enemyY = playerY + RandomGen().getRand(20, 18);
	CompShip enemy(enemyX, enemyY, enemyTextureID);
	addNewEnemy(enemy);
	std::cout << "ADDED NEW ENEMY: " << enemyList.size() << std::endl;
}

void EnemyList::addNewEnemy(CompShip enemy)
{
	enemyList.push_back(enemy);
}

void EnemyList::setAsteroidList(Map* asteroidMapListRef)
{
	this->asteroidMapListRef = asteroidMapListRef;
}

void EnemyList::updateAllEnemies(double playerX, double playerY, double deltaT)
{
	explosionList.removeExplosions();
	enemyBullets.remove(playerX, playerY);
	if (enemyBullets.getSize() > 0)
	{
		enemyBullets.updataAllBullets(deltaT);
	}
	
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i].updateCompShip(playerX, playerY, deltaT);

		if (enemyList[i].readyToFire())
		{
			Bullet newBullet(enemyList[i].getCompX(), enemyList[i].getCompY(), playerX, playerY, 0, enemyBulletTextureID);
			enemyBullets.add(newBullet);
			Bullet newBullet1(enemyList[i].getCompX(), enemyList[i].getCompY(), playerX, playerY, 1, enemyBulletTextureID);
			enemyBullets.add(newBullet1);
			std::cout << "Enemy bullet vector size: " << enemyBullets.getSize() << std::endl;
		}
	}
	explosionList.updateAllExplosions(deltaT);
}

void EnemyList::setEnemyBulletTexture(GLuint* BulletTextureID, GLuint* explosionTextureID)
{
	enemyBulletTextureID = BulletTextureID;
	this->explosionTextureID = explosionTextureID;
}

void EnemyList::drawAllEnemies()
{
	enemyBullets.drawAllBullets();
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i].drawCompShip();
	}
	explosionList.drawAllExplosions();
}

EnemyProjectiles* EnemyList::getEnemyBullets()
{
	return &enemyBullets;
}

void EnemyList::checkCollisions(PlayerProjectiles& playerProjectiles)
{
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		Point enemy(enemyList[i].getCompX(), enemyList[i].getCompY());
		for (unsigned int j = 0; j < playerProjectiles.getSize(); j++)
		{
			if (Collision().checkCollision(&playerProjectiles.getVector()[j].box, &enemy, 0.97))
			{
				Bullet* b = playerProjectiles.getBullet(j);
				b->destroy();
				enemyList[i].destroyed = true;
				Explosion explosion(enemyList[i].compX, enemyList[i].compY, explosionTextureID);
				explosionList.addExplosion(explosion);
			}
		}

		for (unsigned int j = 0; j < enemyList.size(); j++)
		{
			Point p2(enemyList[j].getCompX(), enemyList[j].getCompY());
			if (i != j && Collision().isIntersect(enemyList[i].box, enemy, enemyList[j].box, p2, 28, minTransDist))
			{
				enemyList[i].setMinTransDist(minTransDist.pointX * 0.5, minTransDist.pointY * 0.5);
				enemyList[j].setMinTransDist(-minTransDist.pointX * 0.5, -minTransDist.pointY * 0.5);
			}
		}

		for (unsigned int j = 0; j < asteroidMapListRef->asteroidField.size(); j++)
		{
			Point p2(asteroidMapListRef->asteroidField[j].getRoidX(), asteroidMapListRef->asteroidField[j].getRoidY());
			if (Collision().isIntersect(enemyList[i].box, 
				enemy,
				asteroidMapListRef->asteroidField[j].box, 
				p2,
				28,
				minTransDist))
			{
				enemyList[i].setMinTransDist(minTransDist.pointX * 2, minTransDist.pointY * 2);
			}
		}
	}

	for (unsigned int i = 0; i < playerProjectiles.getSize(); i++)
	{
		Bullet* b = playerProjectiles.getBullet(i);
		Point p1(b->getX(), b->getY());
		
		for (unsigned int j = 0; j < asteroidMapListRef->asteroidField.size(); j++)
		{
			Point p2(asteroidMapListRef->asteroidField[j].getRoidX(), asteroidMapListRef->asteroidField[j].getRoidY());
			if (Collision().isIntersect(b->box, p1, asteroidMapListRef->asteroidField[j].box, p2, 28, minTransDist))
			{
				b->destroyed = true;
			}
		}
	}
}

void EnemyList::remove()
{
	if (enemyList.size() > 0)
	{
		std::vector<CompShip>::iterator it = enemyList.begin();
		while (it != enemyList.end())
		{
			if (it->destroyed == true)
			{
				it = enemyList.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

CompShip* EnemyList::getShip(unsigned int index)
{
	return &enemyList[index];
}
