#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "SOIL.h"
#include "OpenGLApplication.h"
#include "PlayerShip.h"
#include "EnemyProjectiles.h"
#include "CompShip.h"
#include "Collision.h"
#include "MyTranslate.h"
#include <iostream>


const double PLAYER_MOVEMENT_SPEED = 10.0;
const double PI = 3.14159265359;
const double UPPER_SPEED_THRESHOLD = 65;
const double LOWER_SPEED_THRESHOLD = 0;
const double PLAYER_ROTATION_SPEED = 2.5;

double p_rMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double p_tMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double p_aMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double p_xyhVector[3] = { 0.0, 0.0, 0.0 };
double p_aVector[3] = { 0.0, 0.0, 0.0 };

PlayerShip::PlayerShip(){}

PlayerShip::PlayerShip(double x, double y)
{
	this->playerX = x;
	this->playerY = y;
	this->playerRotation = 0;
	this->playerSpeed = 0;
	this->fireFreq = 0;
	this->dx = 0.0;
	this->dy = 0.0;
	this->gotHit = false;
	this->flash = 0;
	this->flashCount = 0;
	this->shipHP = 100;
	this->collected = 0;
	this->killed = 0;
	this->box = BoundingQuad(5);
	this->playerMinTransDist = Point(0, 0);

	//Reference points.
	box.points[0].setPoint(-1, -2);
	box.points[1].setPoint(1, -2);
	box.points[2].setPoint(1, 0);
	box.points[3].setPoint(0, 2);
	box.points[4].setPoint(-1, 0);
	//Points to be moved.
	box.pointsN[0].setPoint(-1, -2);
	box.pointsN[1].setPoint(1, -2);
	box.pointsN[2].setPoint(1, 0);
	box.pointsN[3].setPoint(0, 2);
	box.pointsN[4].setPoint(-1, 0);
}

PlayerShip::~PlayerShip(){}

void PlayerShip::setImages(GLuint* playerTextureID, GLuint* playerHitTextureID)
{
	this->playerHitTextureID = playerHitTextureID;
	this->playerTextureID = playerTextureID;

	this->drawTexture = *playerTextureID;
}

bool PlayerShip::isReadyToFire()
{
	if (fireFreq > 1.5)
	{
		fireFreq = 0;
		return true;
	}
	return false;
}

void PlayerShip::setEnemyList(EnemyList* enemyShipListRef)
{
	this->enemyShipListRef = enemyShipListRef;
}

void PlayerShip::setAsteroidList(Map* asteroidMapListRef)
{
	this->asteroidMapListRef = asteroidMapListRef;
}

void PlayerShip::setCollectableList(CollectableList* collectableList)
{
	this->collectableList = collectableList;
}

void PlayerShip::playerUpdate(double deltaT)
{
	if (gotHit)
	{
		showHit(deltaT);
	}

	//Convert the angle to radians for use with sin and cos.
	dx = cos(toRadians(playerRotation + 90));
	dy = sin(toRadians(playerRotation + 90));
	
	playerX += dx * playerSpeed * deltaT / 10;
	playerY += dy * playerSpeed * deltaT / 10;
	fireFreq += (5 * deltaT);

	playerX += playerMinTransDist.pointX;
	playerY += playerMinTransDist.pointY;
	playerMinTransDist.pointX = 0;
	playerMinTransDist.pointY = 0;

	//Enemy bullet collision detection...
	for (unsigned int i = 0; i < enemyBullets->getSize(); i++)
	{
		Bullet* eBullet = enemyBullets->getBullet(i);
		if (Collision().isIntersect(this->box, Point(playerX, playerY), eBullet->box, Point(eBullet->getX(), eBullet->getY()), 28,bulletMinTransDist))
		{
			gotHit = true;
			shipHP--;
			//std::cout << "LIFE LEFT: " << shipHP << std::endl;
			eBullet->destroy();
		}
	}

	//Enemy ship collision detection...
	for (unsigned int i = 0; i < this->enemyShipListRef->getSize(); i++)
	{
		CompShip* eShip = enemyShipListRef->getShip(i);
		Point enemyMinTransDist;
		if (Collision().isIntersect(this->box, Point(playerX, playerY), eShip->box, Point(eShip->getCompX(), eShip->getCompY()), 28, enemyMinTransDist))
		{
			gotHit = true;
			shipHP-= 0.1;
			//std::cout << "LIFE LEFT: " << shipHP << std::endl;

			playerMinTransDist = Point(enemyMinTransDist.pointX * 0.1, enemyMinTransDist.pointY * 0.1);
			eShip->setMinTransDist(-enemyMinTransDist.pointX * 0.9, -enemyMinTransDist.pointY * 0.9);
		}
	}

	//Player / asteroid collision
	Point minTransDist;
	for (unsigned i = 0; i < asteroidMapListRef->asteroidField.size(); i++)
	{
		{
			if (Collision().isIntersect(this->box, Point(playerX, playerY), 
				asteroidMapListRef->asteroidField[i].box, 
				Point(asteroidMapListRef->asteroidField[i].getRoidX(), asteroidMapListRef->asteroidField[i].getRoidY()), 28,
				minTransDist))
			{
				this->setMinTransDist(minTransDist.pointX, minTransDist.pointY);
				showHit(deltaT);
				shipHP -= 0.1;
				//std::cout << "LIFE LEFT: " << shipHP << std::endl;
				playerSpeedDown(deltaT * 2.5);
			}
		}
	}

	//Enemy bullet / asteroid collision.
	for (unsigned int i = 0; i < enemyBullets->getSize(); i++)
	{
		Bullet* eBullet = enemyBullets->getBullet(i);
		Point p1(eBullet->getX(), eBullet->getY());

		for (unsigned int j = 0; j < asteroidMapListRef->asteroidField.size(); j++)
		{
			Point p2(asteroidMapListRef->asteroidField[j].getRoidX(), asteroidMapListRef->asteroidField[j].getRoidY());
			if (Collision().isIntersect(eBullet->box, p1, asteroidMapListRef->asteroidField[j].box, p2, 28, minTransDist))
			{
					eBullet->destroyed = true;
			}
		}
	}

	Point collectMinTransVec;
	for (unsigned int i = 0; i < collectableList->getSize(); i++)
	{
		Collectable* collectable = collectableList->getCollectable(i);
		if (Collision().isIntersect(this->box, 
			Point(playerX, playerY), 
			collectable->box,
			Point(collectable->getCollectX(), collectable->getCollectY()), 
			28, 
			collectMinTransVec))
		{
			collectable->collected = true;
			collected++;
			PlaySound("sounds/collect.wav", NULL, SND_ASYNC);
		}
	}
}

void PlayerShip::incrementKill()
{
	killed++;
}

void PlayerShip::playerSpeedUp(double deltaT)
{
	//player upper speed restriction...
	playerSpeed += 50 * deltaT;
	if (playerSpeed > UPPER_SPEED_THRESHOLD)
	{
		playerSpeed = UPPER_SPEED_THRESHOLD;
	}
}

void PlayerShip::playerSpeedDown(double deltaT)
{
	//player lower speed restriction...
	//Slowing down is slower than accelrating. This is intentional.
	playerSpeed -= 25 * deltaT;
	if (playerSpeed < LOWER_SPEED_THRESHOLD)
	{
		playerSpeed = LOWER_SPEED_THRESHOLD;
	}
}

void PlayerShip::setEnemyBullets(EnemyProjectiles* enemyBullets)
{
	this->enemyBullets = enemyBullets;
}

void PlayerShip::playerShoot(double deltaT)
{
	//Not sure if should just return ready to shoot or put whole shoot mechanic here.
}

void PlayerShip::playerRotateLeft(double deltaT)
{
	playerRotation += PLAYER_ROTATION_SPEED * deltaT * 40;
}

void PlayerShip::playerRotateRight(double deltaT)
{
	playerRotation -= PLAYER_ROTATION_SPEED * deltaT * 40;
}

void PlayerShip::setMinTransDist(double xTrans, double yTrans)
{
	playerMinTransDist = Point(xTrans, yTrans);
}

void PlayerShip::playerDraw()
{
	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Use transparency for PNG image.

	// Move the player to the required position
	//glTranslatef(playerX, playerY, 0.0);
	MyTranslate().makeTranslateMatrix(playerX, playerY, p_tMatrix);

	//glRotatef(playerRotation, 0.0, 0.0, 1.0);
	MyTranslate().makeRotateMatrix(playerRotation * PI / 180, p_rMatrix);

	MyTranslate().multiplyTwoMatrix(p_tMatrix, p_rMatrix, p_aMatrix);

	for (unsigned int i = 0; i < box.getSize(); i++)
	{
		MyTranslate().makeXYHVector(box.points[i].pointX, box.points[i].pointY, p_xyhVector);
		MyTranslate().multiplyMatrixPostVector(p_aMatrix, p_xyhVector, p_aVector);
		box.pointsN[i].pointX = p_aVector[0];
		box.pointsN[i].pointY = p_aVector[1];
	}

	// Bind our player texture to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, drawTexture);
	
	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	// Use two triangles to make a square, with texture co-ordinates for each vertex
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0, 0);
	glVertex2f(box.pointsN[0].pointX, box.pointsN[0].pointY);

	glTexCoord2f(1, 0);
	glVertex2f(box.pointsN[1].pointX, box.pointsN[1].pointY);

	glTexCoord2f(1, 0.5);
	glVertex2f(box.pointsN[2].pointX, box.pointsN[2].pointY);

	glTexCoord2f(0.5, 1);
	glVertex2f(box.pointsN[3].pointX, box.pointsN[3].pointY);

	glTexCoord2f(0, 0.5);
	glVertex2f(box.pointsN[4].pointX, box.pointsN[4].pointY);

	glEnd();

	// Disable 2D texturing
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
	//glFlush();
}

double PlayerShip::getPlayerX()
{
	return this->playerX;
}

double PlayerShip::getPlayerY()
{
	return this->playerY;
}

double PlayerShip::getPlayerRot()
{
	return this->playerRotation;
}

double PlayerShip::toRadians(double angle)
{
	return angle * PI / 180;
}

double PlayerShip::toDegrees(double radians)
{
	return radians * 180 / PI;
}

double PlayerShip::getPlayerSpeed()
{
	return this->playerSpeed;
}

void PlayerShip::showHit(double deltaT)
{
	flash += deltaT * 10;
	if (flash > 1)
	{
		drawTexture = *playerTextureID;
		flash = 0;
		flashCount++;
	}
	else if (flash > 0.5)
	{
		drawTexture = *playerHitTextureID;
	}
	if (flashCount > 2)
	{
		gotHit = false;
		flashCount = 0;
	}
	drawTexture = *playerTextureID;
}