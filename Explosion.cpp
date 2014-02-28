#include "Explosion.h"
#include <iostream>


Explosion::Explosion()
{
	this->explosionX = 0;
	this->explosionY = 0;
	this->freq = 0;
	this->xFrame = 1.0 / 8;
	this->yFrame = 1.0 / 6;
	this->xFrameCount = 0;
	this->yFrameCount = 5;
}

Explosion::Explosion(double exploX, double exploY, GLuint* explosionTextureID)
{
	this->explosionX = exploX;
	this->explosionY = exploY;
	this->freq = 0;
	this->xFrame = 1.0 / 5;
	this->yFrame = 1.0 / 3;
	this->xFrameCount = 0;
	this->yFrameCount = 2;
	this->finished = false;
	std::cout << this->xFrameCount << "\t" << yFrameCount << "\t" << this->explosionX << "\t" << explosionY << std::endl;
	this->explosionTextureID = *explosionTextureID;
	std::cout << this->explosionTextureID << std::endl;
}



Explosion::~Explosion()
{
}

void Explosion::setExplosion(double exploX, double exploY, GLuint* explosionTextureID)
{

	this->explosionX = exploX;
	this->explosionY = exploY;
	std::cout << "F count " <<this->xFrameCount << "\t" << yFrameCount << std::endl;
	this->explosionTextureID = *explosionTextureID;
	std::cout << this->explosionTextureID << std::endl;
}

void Explosion::updateExplosion(double deltaT)
{
	freq += (1 * deltaT);
	if (freq > 0.05 && !finished)
	{
		if (++xFrameCount >= 4)
		{
			xFrameCount = 0;
			if (--yFrameCount <= 0)
			{
				yFrameCount = 2;				
				finished = true;
			}
		}
		freq = 0;
	}
}

void Explosion::drawExplosion()
{
	std::cout << "DRAWING EXPLOSION" << std::endl;
	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Use transparency for PNG image.

	// Move the player to the required position
	glTranslatef(explosionX, explosionY, 0.0);

	// Bind our player texture to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, explosionTextureID);

	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);


	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0 + (xFrameCount * xFrame), 0 + (yFrameCount * yFrame));
	glVertex2f(-1.5, -1.5);

	glTexCoord2f(xFrame + (xFrameCount * xFrame), 0 + (yFrameCount * yFrame));
	glVertex2f(1.5, -1.5);

	glTexCoord2f(xFrame + (xFrameCount * xFrame), yFrame + (yFrameCount * yFrame));
	glVertex2f(1.5, 1.5);

	glTexCoord2f(0 + (xFrameCount * xFrame), yFrame + (yFrameCount * yFrame));
	glVertex2f(-1.5, 1.5);

	glEnd();

	// Disable 2D texturing
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glPopMatrix();
}