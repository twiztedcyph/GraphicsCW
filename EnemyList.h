#pragma once
#include "CompShip.h"
#include "PlayerProjectiles.h"
#include "EnemyProjectiles.h"
#include "Map.h"
#include "ExplosionList.h"


class EnemyList
{
private:
	GLuint* enemyBulletTextureID;
	GLuint* explosionTextureID;
	std::vector<CompShip> enemyList;
	EnemyProjectiles enemyBullets;
	Point minTransDist;
	Map* asteroidMapListRef;
	ExplosionList explosionList;
public:
	EnemyList();
	~EnemyList();

	int getSize();
	
	void addNewEnemy(CompShip newEnemy);

	void setEnemyBulletTexture(GLuint* enemyBulletTextureID, GLuint* explosionTextureID);

	void spawnNewRandom(double playerY, double playerX, GLuint* enemyTextureID);

	void updateAllEnemies(double playerX, double playerY, double deltaT);

	void checkCollisions(PlayerProjectiles& playerProjectiles);

	void setAsteroidList(Map* asteroidMapListRef);

	void drawAllEnemies();

	void remove();

	EnemyProjectiles* getEnemyBullets();

	CompShip* getShip(unsigned int index);
};

