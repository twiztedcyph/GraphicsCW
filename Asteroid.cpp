#include "Asteroid.h"
#include "MyTranslate.h"
#include <iostream>
#include "RandomGen.h"

const double PI = 3.14159265359;
double a_rMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double a_tMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double a_aMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double a_xyhVector[3] = { 0.0, 0.0, 0.0 };
double a_aVector[3] = { 0.0, 0.0, 0.0 };
double xFrame = 1.0 / 5;
double yFrame = 1.0 / 4;
int xPos, yPos;
double freq;

Asteroid::Asteroid(double roidX, double roidY, GLuint* asteroidTextureID)
{
	this->roidX = roidX;
	this->roidY = roidY;
	this->dx = 0;
	this->dy = 0;
	this->roidSpeed = 0;
	this->roidRot = 0;
	this->animate = false;
	this->asteroidTextureID = asteroidTextureID;
	freq = 0;
	xPos = 0;
	yPos = 3;
	box.points[0].setPoint(-2.5, -2.5);
	box.points[1].setPoint(2.5, -2.5);
	box.points[2].setPoint(2.5, 2.5);
	box.points[3].setPoint(-2.5, 2.5);
	box.pointsN[0].setPoint(-2.5, -2.5);
	box.pointsN[1].setPoint(2.5, -2.5);
	box.pointsN[2].setPoint(2.5, 2.5);
	box.pointsN[3].setPoint(-2.5, 2.5);
}

Asteroid::Asteroid(double roidX, double roidY, double roidSpeed, GLuint* asteroidTextureID)
{
	this->roidX = roidX;
	this->roidY = roidY;
	this->dx = 0;
	this->dy = -1;
	this->roidSpeed = roidSpeed;
	this->roidRot = 1;
	this->animate = false;
	this->asteroidTextureID = asteroidTextureID;
	freq = 0;
	xPos = 0;
	yPos = 3;
	box.points[0].setPoint(-2.5, -2.5);
	box.points[1].setPoint(2.5, -2.5);
	box.points[2].setPoint(2.5, 2.5);
	box.points[3].setPoint(-2.5, 2.5);
	box.pointsN[0].setPoint(-2.5, -2.5);
	box.pointsN[1].setPoint(2.5, -2.5);
	box.pointsN[2].setPoint(2.5, 2.5);
	box.pointsN[3].setPoint(-2.5, 2.5);
}

void Asteroid::setAnimate(bool animate)
{
	this->animate = animate;
}

void Asteroid::setRoidSpeed(double roidSpeed)
{
	this->roidSpeed = roidSpeed;
}

void Asteroid::setRoidPos(double roidX, double roidY)
{
	this->roidX = roidX;
	this->roidY = roidY;
}

double Asteroid::getRoidspeed()
{
	return this->roidSpeed;
}

double Asteroid::getRoidX()
{
	return this->roidX;
}

double Asteroid::getRoidY()
{
	return this->roidY;
}

void Asteroid::updateRoid(double deltaT)
{
	if (roidSpeed > 0 && roidY > -228)
	{
		roidX += dx * roidSpeed * deltaT;
		roidY += dy * roidSpeed * deltaT;
		roidRot += deltaT * roidSpeed;
	}
	else if (roidSpeed > 0 && roidY <= -228)
	{
		roidY = 18;
	}
}

void Asteroid::drawRoid()
{
	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Use transparency for PNG image.

	// Move the player to the required position
	//glTranslatef(playerX, playerY, 0.0);
	MyTranslate().makeTranslateMatrix(this->roidX, this->roidY, a_tMatrix);
	//glRotatef(playerRotation, 0.0, 0.0, 1.0);
	MyTranslate().makeRotateMatrix(roidRot, a_rMatrix);

	MyTranslate().multiplyTwoMatrix(a_tMatrix, a_rMatrix, a_aMatrix);

	for (unsigned int i = 0; i < 4; i++)
	{
		MyTranslate().makeXYHVector(box.points[i].pointX, box.points[i].pointY, a_xyhVector);
		MyTranslate().multiplyMatrixPostVector(a_aMatrix, a_xyhVector, a_aVector);
		box.pointsN[i].pointX = a_aVector[0];
		box.pointsN[i].pointY = a_aVector[1];
	}

	// Bind our player texture to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, *this->asteroidTextureID);

	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	// Use two triangles to make a square, with texture co-ordinates for each vertex
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0 + (xPos * xFrame), 0 + (yPos * yFrame));
	glVertex2f(box.pointsN[0].pointX, box.pointsN[0].pointY);

	glTexCoord2f(xFrame + (xPos * xFrame), 0 + (yPos * yFrame));
	glVertex2f(box.pointsN[1].pointX, box.pointsN[1].pointY);

	glTexCoord2f(xFrame + (xPos * xFrame), yFrame + (yPos * yFrame));
	glVertex2f(box.pointsN[2].pointX, box.pointsN[2].pointY);

	glTexCoord2f(0 + (xPos * xFrame), yFrame + (yPos * yFrame));
	glVertex2f(box.pointsN[3].pointX, box.pointsN[3].pointY);


	glEnd();

	// Disable 2D texturing
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	glPopMatrix();
	//glFlush();
}