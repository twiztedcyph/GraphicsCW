#pragma once
#include <windows.h>		// Header File For Windows.
#include <gl\gl.h>			// Header File For The OpenGL32 Library.
#include <gl\glu.h>			// Header File For The GLu32 Library.
#include "BoundingQuad.h"

class Collectable
{
private:
	double collectX, collectY;
	GLuint* collectTextureID;
	double xFrame;
	double yFrame;
	int xPos, yPos;
	double freq;
public:
	bool collected;
	BoundingQuad box;
	Collectable(double collectX, double collectY, GLuint* collectTextureID);
	Collectable();
	~Collectable();

	double getCollectX();
	double getCollectY();

	void updateCollectable(double deltaT);
	void drawCollectable();
};

