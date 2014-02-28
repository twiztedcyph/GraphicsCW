#pragma once
#include <windows.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>
#include "BoundingQuad.h"

class Bullet
{
private:
	double xPos, yPos;
	double xVel, yVel;
	double bulletAngle;
	GLuint* bulletTextureID;
	bool doubleGun;
	int side;

public:
	bool destroyed;
	double ttl;

	BoundingQuad box;
	Bullet(double xPos, double yPos, double angle, GLuint* bulletTextureID);
	Bullet(double xPos, double yPos, double xTarget, double yTarget, int side,GLuint* bulletTextureID);
	~Bullet();
	void setXVel(double xVel);
	void setYVel(double yVel);
	void setXPos(double xPos);
	void setYPos(double yPos);
	double getX();
	double getY();

	void destroy();

	void updateBullet(double deltaT);

	void drawBullet();
};

