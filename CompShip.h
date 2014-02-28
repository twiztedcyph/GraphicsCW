#pragma once
#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "BoundingQuad.h"

class CompShip
{
private:
	int enemyType;
	GLuint* enemyTextureID;
	double angle;
	double cAngle;
	Point minTransDist;
public:
	double compX, compY, dx, dy, fireFreq, mult, distToPlayer;
	BoundingQuad box;
	bool destroyed, colliding;
	CompShip(double compX, double compY, GLuint* enemyTextureID);
	~CompShip();
	void updateCompShip(double playerX, double playerY, double deltaT);
	void drawCompShip();
	//void rebound(double deltaT);

	bool readyToFire();
	double getAngle();
	double getCompX();
	double getCompY();
	void setCompX(double x);
	void setCompY(double y);
	void setMinTransDist(double xTrans, double yTrans);
	double getDX();
	double getDY();
	double getAngleToOther(CompShip otherShip);
	double getAngleToOther(double xPos, double yPos);
	void setDX(double dx);
	void setDY(double dy);

	void setCAngle(double cAngle);

	double getSpeed();
	void setSpeed(double speed);
};

