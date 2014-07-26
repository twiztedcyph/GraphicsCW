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

const double PI = 3.14159265359;

EnemyList::EnemyList()
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
	CompShip enemy(0, enemyX, enemyY, enemyTextureID);
	addNewEnemy(enemy);
	//std::cout << "ADDED NEW ENEMY: " << enemyList.size() << std::endl;
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
	this->playerShipX = playerX;
	this->playerShipY = playerY;
	if (enemyBullets.getSize() > 0)
	{
		enemyBullets.updataAllBullets(deltaT);
	}
	
	for (unsigned int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i].updateCompShip(playerX, playerY, deltaT);

		if (enemyList[i].enemyType == 1 && enemyList[i].readyToSpawn())
		{
			double tAngle = atan2(enemyList[i].dy, enemyList[i].dx);
			std::cout << tAngle << std::endl;
			CompShip compShip1(0, (enemyList[i].compX + cos(tAngle)), enemyList[i].compY + sin(tAngle), enemyTextureID);
			enemyList.push_back(compShip1);
		}

		if (enemyList[i].enemyType == 0 && enemyList[i].readyToFire())
		{
			Bullet newBullet(enemyList[i].getCompX(), enemyList[i].getCompY(), playerX, playerY, 0, enemyBulletTextureID);
			enemyBullets.add(newBullet);
			Bullet newBullet1(enemyList[i].getCompX(), enemyList[i].getCompY(), playerX, playerY, 1, enemyBulletTextureID);
			enemyBullets.add(newBullet1);
		}
		else if (enemyList[i].enemyType == 1 && enemyList[i].readyToFire())
		{
			Bullet newBullet(enemyList[i].getCompX(), enemyList[i].getCompY(), playerX, playerY, 0, enemyBulletTextureID);
			enemyBullets.add(newBullet);
			Bullet newBullet1(enemyList[i].getCompX(), enemyList[i].getCompY(), playerX, playerY, 1, enemyBulletTextureID);
			enemyBullets.add(newBullet1);
		}
	}
	explosionList.updateAllExplosions(deltaT);
}

void EnemyList::setEnemyBulletTexture(GLuint* BulletTextureID, GLuint* explosionTextureID, GLuint* enemyTextureID)
{
	this->enemyBulletTextureID = BulletTextureID;
	this->explosionTextureID = explosionTextureID;
	this->enemyTextureID = enemyTextureID;
}

void EnemyList::setCollectableList(CollectableList* collectableList, GLuint* collectableTextureID)
{
	this->collectableList = collectableList;
	this->collectableTextureID = collectableTextureID;
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
			Bullet* b = playerProjectiles.getBullet(j);
			Point bulPoint(b->getX(), b->getY());
			if (enemyList[i].enemyType == 0 && Collision().checkCollision(playerProjectiles.getVector()[j].box, enemy, 0.97))
			{
				b->destroy();
				enemyList[i].enemyHP--;
				Explosion explosion;
				if (enemyList[i].enemyHP <= 0)
				{
					enemyList[i].destroyed = true;
					if (enemyList[i].enemyType == 0)
					{
						explosion = Explosion(enemyList[i].compX, enemyList[i].compY, 1, explosionTextureID);
					}
					else
					{
						explosion = Explosion(enemyList[i].compX, enemyList[i].compY, 2, explosionTextureID);
					}
					
					explosionList.addExplosion(explosion);
				}
			}
			else if (enemyList[i].enemyType == 1 && Collision().isIntersect(enemyList[i].box,
				enemy,
				b->box,
				bulPoint,
				28,
				minTransDist))
			{
				b->destroy();
				enemyList[i].enemyHP--;
				if (enemyList[i].enemyHP <= 0)
				{
					enemyList[i].destroyed = true;
					Explosion explosion(enemyList[i].compX, enemyList[i].compY, 1, explosionTextureID);
					explosionList.addExplosion(explosion);
				}
			}
		}

		for (unsigned int j = 0; j < enemyList.size(); j++)
		{
			Point p2(enemyList[j].getCompX(), enemyList[j].getCompY());
			if (i != j && Collision().isIntersect(enemyList[i].box, enemy, enemyList[j].box, p2, 28, minTransDist))
			{
				if (enemyList[i].enemyType == 1)
				{
					enemyList[j].setMinTransDist(minTransDist.pointX, minTransDist.pointY);
				}
				else if (enemyList[j].enemyType == 1)
				{
					enemyList[i].setMinTransDist(minTransDist.pointX, minTransDist.pointY);
				}
				else
				{
					enemyList[i].setMinTransDist(minTransDist.pointX * 0.5, minTransDist.pointY * 0.5);
					enemyList[j].setMinTransDist(-minTransDist.pointX * 0.5, -minTransDist.pointY * 0.5);
				}
			}
		}

		Point playerPos(playerShipX, playerShipY);
		//std::cout << playerPos.pointX << "\t" << playerPos.pointY << "\t" << enemy.pointX << "\t" << enemy.pointY << std::endl;
		BoundingQuad lineBox(playerPos, playerPos, enemy, enemy);
		bool result = true;
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
				enemyList[i].turnAround();
			}
			if (!Collision().hasLineOfSight(enemy, playerPos, lineBox, asteroidMapListRef->asteroidField[j].box, p2, 28))
			{
				result = false;
			}
		}
		enemyList[i].setLOS(result);
	}

	for (unsigned int i = 0; i < playerProjectiles.getSize(); i++)
	{
		Bullet* b = playerProjectiles.getBullet(i);
		Point p1(b->getX(), b->getY());
		
		for (unsigned int j = 0; j < asteroidMapListRef->asteroidField.size(); j++)
		{
			Point p2(asteroidMapListRef->asteroidField[j].getRoidX(), asteroidMapListRef->asteroidField[j].getRoidY());
			if (Collision().isIntersect(b->box, p1, asteroidMapListRef->asteroidField[j].box, p2, 40, minTransDist))
			{
				Explosion explosion(b->box.pointsN[2].pointX, b->box.pointsN[2].pointY, 0.3, explosionTextureID);
				explosionList.addExplosion(explosion);
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
