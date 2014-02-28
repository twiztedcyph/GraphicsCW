#include <windows.h>		// Header File For Windows.
#include <gl\gl.h>			// Header File For The OpenGL32 Library.
#include <gl\glu.h>			// Header File For The GLu32 Library.
#include "Star.h"
#include "RandomGen.h"
#include "PlayerShip.h"

Star::Star(){}

Star::Star(double x, double y, double yVel, double xVel, int size)
{
	this->xPos = x;
	this->yPos = y;
	this->yVel = yVel;
	this->xVel = xVel;
	this->size = size;
}

Star::~Star(){}

void Star::set(double x, double y, double yVel, double xVel, int size)
{
	this->xPos = x;
	this->yPos = y;
	this->yVel = yVel;
	this->xVel = xVel;
	this->size = size;
}

double Star::getXPos()
{
	return this->xPos;
}

double Star::getYPos()
{
	return this->yPos;
}

void Star::setXPos(double x)
{
	this->xPos;
}

void Star::setYPos(double y)
{
	this->yPos;
}

void Star::move(double deltaT, double playerDx, double playerDy, double playerSpeed)
{
	//For when camera goes left.
	//Remove magic numbers.
	xPos -= playerDx * playerSpeed * deltaT * xVel;
	yPos -= playerDy * playerSpeed * deltaT * yVel;
}


void Star::update(double camY, double camX)
{
	if (camY - yPos > 17)
	{
		yPos = (camY + RandomGen().getRand(18, 15));
		xPos += RandomGen().getRand(20, -20);
	}
	else if (camY - yPos < -17)
	{
		yPos = (camY - RandomGen().getRand(18, 15));
		xPos += RandomGen().getRand(20, -20);
	}
	else if (camX - xPos > 32)
	{
		xPos = (camX + RandomGen().getRand(30, 30));
		yPos += RandomGen().getRand(18, -18);
	}
	else if (camX - xPos < -32)
	{
		xPos = (camX - RandomGen().getRand(30, 30));
		yPos += RandomGen().getRand(18, -18);
	}
}

void Star::draw()
{
	glPushMatrix();
	
	glEnable(GL_POINT_SMOOTH);
	glPointSize(size);
	
	glBegin(GL_POINTS);
	switch (size)
	{
	case 1:
		glColor3f(0.4f, 0.4f, 0.4f);
		break;
	case 2:
		glColor3f(0.6f, 0.6f, 0.6f);
		break;
	case 3:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	default:
		//Should never reach here...
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	}
	glVertex2d(xPos, yPos);
	glEnd();
	
	glDisable(GL_POINT_SMOOTH);
	glPopMatrix();
}