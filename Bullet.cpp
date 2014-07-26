#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "SOIL.h"
#include "OpenGLApplication.h"
#include "Bullet.h"
#include "BoundingQuad.h"
#include "MyTranslate.h"
#include <iostream>

const double PI = 3.14159265;

//GLuint bulletTextureID;
double b_rMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double b_tMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double b_aMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double b_xyhVector[3] = { 0.0, 0.0, 0.0 };
double b_aVector[3] = { 0.0, 0.0, 0.0 };


Bullet::Bullet(double xPos, double yPos, double angle, GLuint* bulletTextureID)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->xVel = 0;
	this->yVel = 15;
	this->bulletTextureID = bulletTextureID;
	this->destroyed = false;
	this->bulletAngle = angle;
	this->doubleGun = false;
	box.points[0].setPoint(-0.1, -0.25);
	box.points[1].setPoint(-0.1, 0.25);
	box.points[2].setPoint(0.1, 0.25);
	box.points[3].setPoint(0.1, -0.25);
	box.pointsN[0].setPoint(-0.1, -0.25);
	box.pointsN[1].setPoint(-0.1, 0.25);
	box.pointsN[2].setPoint(0.1, 0.25);
	box.pointsN[3].setPoint(0.1, -0.25);
	ttl = 20;
}

Bullet::Bullet(double xPos, double yPos, double xTarget, double yTarget, int side, GLuint* bulletTextureID)
{
	std::cout << *bulletTextureID << std::endl;
	this->xPos = xPos;
	this->yPos = yPos;
	this->xVel = 0;
	this->yVel = 15;
	this->bulletTextureID = bulletTextureID;
	this->destroyed = false;
	this->doubleGun = true;
	this->side = side;
	this->bulletAngle = (atan2(yTarget - yPos, xTarget - xPos) * 180 / PI) - 90;
	box.points[0].setPoint(-0.1, -0.25);
	box.points[1].setPoint(-0.1, 0.25);
	box.points[2].setPoint(0.1, 0.25);
	box.points[3].setPoint(0.1, -0.25);
	box.pointsN[0].setPoint(-0.1, -0.25);
	box.pointsN[1].setPoint(-0.1, 0.25);
	box.pointsN[2].setPoint(0.1, 0.25);
	box.pointsN[3].setPoint(0.1, -0.25);
	this->ttl = 20;
}

Bullet::~Bullet()
{
}

double Bullet::getX()
{
	return this->xPos;
}

double Bullet::getY()
{
	return this->yPos;
}

void Bullet::setXPos(double xPos)
{
	this->xPos = xPos;
}

void Bullet::setYPos(double yPos)
{
	this->yPos = yPos;
}

void Bullet::setXVel(double xVel)
{
	this->xVel = xVel;
}

void Bullet::setYVel(double yVel)
{
	this->yVel = yVel;
}

void Bullet::destroy()
{
	this->destroyed = true;
}

void Bullet::updateBullet(double deltaT)
{
	//std::cout << "Bullet angle: " << this->bulletAngle << std::endl;
	if (!destroyed)
	{
		double rad = (bulletAngle + 90) / 180 * 3.14159265359;
		xVel = cos(rad);
		yVel = sin(rad);
		this->xPos += xVel * deltaT * 10;
		this->yPos += yVel * deltaT * 10;
		xVel = yVel = 0;
		rad = (bulletAngle) / 180 * 3.14159265359;
		MyTranslate().makeTranslateMatrix(xPos, yPos, b_tMatrix);
		MyTranslate().makeRotateMatrix(rad, b_rMatrix);
		MyTranslate().multiplyTwoMatrix(b_tMatrix, b_rMatrix, b_aMatrix);
		if (doubleGun)
		{
			MyTranslate().makeTranslateMatrix(side - 0.5, 0.7, b_tMatrix);
		}
		else
		{
			MyTranslate().makeTranslateMatrix(0, 1.7, b_tMatrix);
		}
		MyTranslate().multiplyTwoMatrix(b_aMatrix, b_tMatrix, b_aMatrix);

		for (unsigned int i = 0; i < 4; i++)
		{
			MyTranslate().makeXYHVector(box.points[i].pointX, box.points[i].pointY, b_xyhVector);
			MyTranslate().multiplyMatrixPostVector(b_aMatrix, b_xyhVector, b_aVector);
			box.pointsN[i].pointX = b_aVector[0];
			box.pointsN[i].pointY = b_aVector[1];
		}
		ttl -= 5 * deltaT;
	}
}

void Bullet::drawBullet()
{
	if (!destroyed)
	{
		glPushMatrix();

		glEnable(GL_BLEND);
		
		// Use transparency for PNG image.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Bind our player texture to GL_TEXTURE_2D
		glBindTexture(GL_TEXTURE_2D, *bulletTextureID);

		// Enable 2D texturing
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0, 0);
		glVertex2f(box.pointsN[0].getPointX(), box.pointsN[0].getPointY());

		glTexCoord2f(0, 1);
		glVertex2f(box.pointsN[1].getPointX(), box.pointsN[1].getPointY());

		glTexCoord2f(1, 1);
		glVertex2f(box.pointsN[2].getPointX(), box.pointsN[2].getPointY());

		glTexCoord2f(1, 0);
		glVertex2f(box.pointsN[3].getPointX(), box.pointsN[3].getPointY());

		glEnd();

		// Disable 2D texturing
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
