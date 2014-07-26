#pragma once
#include "CompShip.h"
#include "PlayerProjectiles.h"
#include "EnemyProjectiles.h"
#include "Map.h"
#include "ExplosionList.h"
#include "CollectableList.h"
#include "Collectable.h"

class EnemyList
{
private:
	GLuint* enemyBulletTextureID;
	GLuint* explosionTextureID;
	GLuint* enemyTextureID;
	GLuint* collectableTextureID;
	CollectableList* collectableList;
	std::vector<CompShip> enemyList;
	EnemyProjectiles enemyBullets;
	Point minTransDist;
	Map* asteroidMapListRef;
	ExplosionList explosionList;
	double playerShipX, playerShipY;
public:
	EnemyList();

	int getSize();
	
	void addNewEnemy(CompShip newEnemy);

	void setEnemyBulletTexture(GLuint* BulletTextureID, GLuint* explosionTextureID, GLuint* enemyTextureID);

	void setCollectableList(CollectableList* collectableList, GLuint* collectableTextureID);

	void spawnNewRandom(double playerY, double playerX, GLuint* enemyTextureID);

	void updateAllEnemies(double playerX, double playerY, double deltaT);

	void checkCollisions(PlayerProjectiles& playerProjectiles);

	void setAsteroidList(Map* asteroidMapListRef);

	void drawAllEnemies();

	void remove();

	EnemyProjectiles* getEnemyBullets();

	CompShip* getShip(unsigned int index);
};

