#pragma once
#include <windows.h>		// Header File For Windows.
#include <gl\gl.h>			// Header File For The OpenGL32 Library.
#include <gl\glu.h>			// Header File For The GLu32 Library.
#include "BoundingQuad.h"

class Asteroid
{
private:
	double roidX, roidY, dx, dy, roidSpeed, roidRot;
	bool animate;
	GLuint* asteroidTextureID;
	
public:
	BoundingQuad box;
	Asteroid(double roidX, double roidY, GLuint* asteroidTextureID);
	~Asteroid();

	void setRoidPos(double roidX, double roidY);
	void setRoidSpeed(double roidSpeed);
	double getRoidX();
	double getRoidY();
	double getRoidspeed();

	void setAnimate(bool animate);
	void drawRoid();
	void updateRoid(double deltaT);
};

