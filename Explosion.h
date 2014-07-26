#pragma once
#include <windows.h>		// Header File For Windows.
#include <gl\gl.h>			// Header File For The OpenGL32 Library.
#include <gl\glu.h>			// Header File For The GLu32 Library.

class Explosion
{
private:
	double explosionX, explosionY;
	double freq;
	double xFrame, yFrame;
	double xFrameCount, yFrameCount;
	double scale;
	GLuint explosionTextureID;
	
public:
	bool finished;
	Explosion();
	Explosion(double exploX, double exploY, double scale, GLuint* explosionTextureID);
	void setExplosion(double exploX, double exploY, double scale, GLuint* explosionTextureID);
	void setExplosionTexture(GLuint* explosionTextureID);
	void updateExplosion(double deltaT);
	void drawExplosion();
	~Explosion();
};

