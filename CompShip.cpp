#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "CompShip.h"
#include "RandomGen.h"
#include "SOIL.h"
#include "OpenGLApplication.h"
#include <iostream>
#include <BoundingQuad.h>
#include <math.h>
#include <MyTranslate.h>

#define PI 3.14159265

double e_rMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double e_tMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double e_aMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double e_xyhVector[3] = { 0.0, 0.0, 0.0 };
double e_aVector[3] = { 0.0, 0.0, 0.0 };

CompShip::CompShip(int type, double compX, double compY, GLuint* enemyTextureID)
{
	this->compX = compX;
	this->compY = compY;
	this->enemyType = enemyType;
	this->fireFreq = 0;
	this->destroyed = false;
	this->colliding = false;
	this->hasLineOfSight = false;
	this->enemyTextureID = enemyTextureID;
	this->cAngle = 0.1;
	this->mult = RandomGen().getRand(1, -1);
	this->minTransDist = Point(0, 0);
	this->enemyType = type;
	box = BoundingQuad(4);

	if (enemyType == 0)
	{
		enemyHP = 1;
		box.points[0].setPoint(-1, -1);
		box.points[1].setPoint(-1, 1);
		box.points[2].setPoint(1, 1);
		box.points[3].setPoint(1, -1);
		box.pointsN[0].setPoint(-1, -1);
		box.pointsN[1].setPoint(-1, 1);
		box.pointsN[2].setPoint(1, 1);
		box.pointsN[3].setPoint(1, -1);
	}
	else
	{
		spawnFreq = 0;
		enemyHP = 5;
		box.points[0].setPoint(-2, -4);
		box.points[1].setPoint(-2, 4);
		box.points[2].setPoint(2, 4);
		box.points[3].setPoint(2, -4);
		box.pointsN[0].setPoint(-2, -4);
		box.pointsN[1].setPoint(-2, 4);
		box.pointsN[2].setPoint(2, 4);
		box.pointsN[3].setPoint(2, -4);
	}
}


CompShip::~CompShip(){}

void CompShip::setCompX(double compX)
{
	this->compX = compX;
}

void CompShip::setCompY(double compY)
{
	this->compY = compY;
}

double CompShip::getCompX()
{
	return this->compX;
}

double CompShip::getCompY()
{
	return this->compY;;
}

void CompShip::setDX(double dx)
{
	this->dx = dx;
}

void CompShip::setDY(double dy)
{
	this->dy = dy;
}

double CompShip::getDX()
{
	return this->dx;
}

double CompShip::getDY()
{
	return this->dy;
}

double CompShip::getAngle()
{
	double result = (this->angle / PI * 180) 
		+ (this->angle > 0 ? 0 : 360);
	return result;
}

void CompShip::setCAngle(double cAngle)
{
	this->cAngle = cAngle;
}

void CompShip::setLOS(bool newLOS)
{
	this->hasLineOfSight = newLOS;
}

void CompShip::updateCompShip(double playerX, 
	double playerY, 
	double deltaT)
{
	if (enemyType == 0)
	{
		if (distToPlayer < 40 && hasLineOfSight)
		{
			this->dx = (playerX - compX);
			this->dy = (playerY - compY);
			fireFreq += deltaT;
		}
		else
		{
			dx = cos(cAngle);
			dy = sin(cAngle);
		}

		this->angle = atan2(dx, dy);
		distToPlayer = sqrt(dx * dx + dy * dy);

		if (distToPlayer != 0)
		{
			dx /= distToPlayer;
			dy /= distToPlayer;
		}

		compX += dx * deltaT * 3.2;
		compY += dy * deltaT * 3.2;

		compX += minTransDist.pointX;
		compY += minTransDist.pointY;
		minTransDist.pointX = 0;
		minTransDist.pointY = 0;
	}
	else if (enemyType == 1)
	{
		//Boss behavior....
		if (distToPlayer < 40 && hasLineOfSight)
		{
			this->dx = (playerX - compX);
			this->dy = (playerY - compY);
			fireFreq += deltaT;
			spawnFreq += deltaT;
		}
		else
		{
			dx = cos(cAngle) * 0.5;
			dy = sin(cAngle) * 0.5;
		}

		this->angle = atan2(dx, dy);
		distToPlayer = sqrt(dx * dx + dy * dy);

		if (distToPlayer != 0)
		{
			dx /= distToPlayer;
			dy /= distToPlayer;
		}

		compX += dx * deltaT * 1.2;
		compY += dy * deltaT * 1.2;

		compX += minTransDist.pointX;
		compY += minTransDist.pointY;
		minTransDist.pointX = 0;
		minTransDist.pointY = 0;
	}
}

void CompShip::setMinTransDist(double xTrans, double yTrans)
{
	this->minTransDist = Point(xTrans, yTrans);
}

double CompShip::getAngleToOther(CompShip otherShip)
{
	double xDist = otherShip.compX - this->compX;
	double yDist = otherShip.compY - this->compY;
	return atan2(xDist, yDist);
}

double CompShip::getAngleToOther(double xPos, double yPos)
{
	double xDist = xPos - this->compX;
	double yDist = yPos - this->compY;
	return atan2(xDist, yDist);
}

bool CompShip::readyToFire()
{
	if (enemyType == 0)
	{
		if (fireFreq > 4 && distToPlayer < 20 && hasLineOfSight)
		{
			fireFreq = 0;
			std::cout << distToPlayer << std::endl;
			return true;
		}
	}
	else
	{
		if (fireFreq > 1 && distToPlayer < 20 && hasLineOfSight)
		{
			fireFreq = 0;
			std::cout << distToPlayer << std::endl;
			return true;
		}
	}
	return false;
}

bool CompShip::readyToSpawn()
{
	if (spawnFreq > 6 && distToPlayer < 20 && hasLineOfSight)
	{
		spawnFreq = 0;
		return true;
	}
	return false;
}

void CompShip::turnAround()
{
	if (mult > 0)
	{
		cAngle += 1.02;
	}
	else
	{
		cAngle -= 1.02;
	}
}

void CompShip::drawCompShip()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	// Use transparency for PNG image.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Move the player to the required position
	
	if (enemyType == 0)
	{
		MyTranslate().makeTranslateMatrix(compX, compY, e_tMatrix);

		// Rotate the enemy to face the player.
		MyTranslate().makeRotateMatrix(-angle, e_rMatrix);

		MyTranslate().multiplyTwoMatrix(e_tMatrix, e_rMatrix, e_aMatrix);
		for (unsigned int i = 0; i < 4; i++)
		{
			MyTranslate().makeXYHVector(box.points[i].pointX,
				box.points[i].pointY,
				e_xyhVector);
			MyTranslate().multiplyMatrixPostVector(e_aMatrix,
				e_xyhVector,
				e_aVector);
			box.pointsN[i].pointX = e_aVector[0];
			box.pointsN[i].pointY = e_aVector[1];
		}


		// Bind our player texture to GL_TEXTURE_2D
		glBindTexture(GL_TEXTURE_2D, *enemyTextureID);

		// Enable 2D texturing
		glEnable(GL_TEXTURE_2D);

		// Use two triangles to make a square, with texture co-ordinates for each vertex
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(box.pointsN[0].pointX, box.pointsN[0].pointY);

		glTexCoord2f(0, 1);
		glVertex2f(box.pointsN[1].pointX, box.pointsN[1].pointY);

		glTexCoord2f(1, 1);
		glVertex2f(box.pointsN[2].pointX, box.pointsN[2].pointY);

		glTexCoord2f(1, 0);
		glVertex2f(box.pointsN[3].pointX, box.pointsN[3].pointY);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		MyTranslate().makeTranslateMatrix(compX, compY, e_tMatrix);

		// Rotate the enemy to face the player.
		MyTranslate().makeRotateMatrix(-angle, e_rMatrix);

		MyTranslate().multiplyTwoMatrix(e_tMatrix, e_rMatrix, e_aMatrix);
		for (unsigned int i = 0; i < 4; i++)
		{
			MyTranslate().makeXYHVector(box.points[i].pointX,
				box.points[i].pointY,
				e_xyhVector);
			MyTranslate().multiplyMatrixPostVector(e_aMatrix,
				e_xyhVector,
				e_aVector);
			box.pointsN[i].pointX = e_aVector[0];
			box.pointsN[i].pointY = e_aVector[1];
		}

		// Bind our player texture to GL_TEXTURE_2D
		glBindTexture(GL_TEXTURE_2D, *enemyTextureID);

		// Enable 2D texturing
		glEnable(GL_TEXTURE_2D);

		// Use two triangles to make a square, with texture co-ordinates for each vertex
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(box.pointsN[0].pointX, box.pointsN[0].pointY);

		glTexCoord2f(0, 1);
		glVertex2f(box.pointsN[1].pointX, box.pointsN[1].pointY);

		glTexCoord2f(1, 1);
		glVertex2f(box.pointsN[2].pointX, box.pointsN[2].pointY);

		glTexCoord2f(1, 0);
		glVertex2f(box.pointsN[3].pointX, box.pointsN[3].pointY);

		glEnd();

		// Disable 2D texturing
		glDisable(GL_TEXTURE_2D);

		//Boss hp
		glBegin(GL_POLYGON);
		
		glColor3f((5 - enemyHP) / (double)5, enemyHP / (double)5, 0.0f);

		glVertex2f(compX - 2, compY - 4);

		glVertex2f(compX - 2, compY - 3.8);

		glVertex2f((compX - 2) + (double)enemyHP / (double)2, compY - 3.8);

		glVertex2f((compX - 2) + (double)enemyHP / (double)2, compY - 4);

		glEnd();
	}

	glDisable(GL_BLEND);
	glPopMatrix();
	//glFlush();
}