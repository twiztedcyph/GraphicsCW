#pragma once
#include "EnemyProjectiles.h"
#include "CompShip.h"
#include "Asteroid.h"
#include "Map.h"
#include <vector>
#include "EnemyList.h"

class PlayerShip
{
private:
	double playerX, playerY, playerSpeed, playerRotation, fireFreq;
	double toRadians(double angle);
	double toDegrees(double radians);
	BoundingQuad box;
	GLuint* playerTextureID;
	GLuint* playerHitTextureID;
	GLuint drawTexture;
	bool gotHit;
	double flash, shipHP;
	int flashCount, killed, lives;
	EnemyList* enemyShipListRef;
	EnemyProjectiles* enemyBullets;
	CollectableList* collectableList;
	Point playerMinTransDist, bulletMinTransDist;
	Map* asteroidMapListRef;
public:
	int collected;
	double dx, dy;
	PlayerShip();
	PlayerShip(double x, double y);
	int ammoLeft;
	~PlayerShip();

	void setImages(GLuint* playerTextureID, GLuint* playerHitTextureID);

	void setCollectableList(CollectableList* collectableList);

	void setEnemyBullets(EnemyProjectiles* enemyBullets);

	void setEnemyList(EnemyList* enemyShipListRef);

	void setPlayerPos(double xPos, double yPos);

	void setAsteroidList(Map* asteroidMapListRef);

	bool isReadyToFire();

	void playerUpdate(double deltaT);

	void setMinTransDist(double xTrans, double yTrans);

	void playerSpeedUp(double deltaT);

	void playerSpeedDown(double deltaT);

	void playerShoot(double deltaT);

	void playerDraw();

	void playerRotateLeft(double deltaT);

	void playerRotateRight(double deltaT);

	void playerMoveLeft(double deltaT);

	void playerMoveRight(double deltaT);

	void showHit(double deltaT);

	void incrementKill();

	bool completedLevelOne();
	bool completedLevelTwo();
	bool completedLevelThree();

	double getPlayerX();
	double getPlayerY();
	double getPlayerRot();
	double getPlayerSpeed();
	double getPlayerHP();
	int getPlayerLives();
};

