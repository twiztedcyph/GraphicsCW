#include "Collectable.h"
#include "MyTranslate.h"


double c_rMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double c_tMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double c_aMatrix[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double c_xyhVector[3] = { 0.0, 0.0, 0.0 };
double c_aVector[3] = { 0.0, 0.0, 0.0 };

Collectable::Collectable()
{
	Collectable(0, 0, 0);
}

Collectable::Collectable(double collectX, double collectY, GLuint* collectTextureID)
{
	this->collectX = collectX;
	this->collectY = collectY;
	this->collectTextureID = collectTextureID;
	this->xFrame = 1.0 / 16;
	this->yFrame = 1.0 / 5;
	this->xPos = 0;
	this->yPos = 4;
	this->freq = 0;
	this->collected = false;
	box.points[0].setPoint(-1, -1);
	box.points[1].setPoint(1, -1);
	box.points[2].setPoint(1, 1);
	box.points[3].setPoint(-1, 1);
	box.pointsN[0].setPoint(-1, -1);
	box.pointsN[1].setPoint(1, -1);
	box.pointsN[2].setPoint(1, 1);
	box.pointsN[3].setPoint(-1, 1);
}


Collectable::~Collectable()
{
}

double Collectable::getCollectX()
{
	return this->collectX;
}

double Collectable::getCollectY()
{
	return this->collectY;
}

void Collectable::updateCollectable(double deltaT)
{
	freq += (1 * deltaT);
	if (freq > 0.05)
	{
		if (++xPos >= 15)
		{
			xPos = 0;
			if (--yPos <= 0)
			{
				yPos = 4;
			}
		}
		freq = 0;
	}
}

void Collectable::drawCollectable()
{
	glPushMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Use transparency for PNG image.

	//glTranslatef(playerX, playerY, 0.0);
	MyTranslate().makeTranslateMatrix(collectX, collectY, c_tMatrix);

	for (unsigned int i = 0; i < box.getSize(); i++)
	{
		MyTranslate().makeXYHVector(box.points[i].pointX, box.points[i].pointY, c_xyhVector);
		MyTranslate().multiplyMatrixPostVector(c_tMatrix, c_xyhVector, c_aVector);
		box.pointsN[i].pointX = c_aVector[0];
		box.pointsN[i].pointY = c_aVector[1];
	}

	// Bind our player texture to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, *collectTextureID);

	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);


	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0 + (xPos * xFrame), 0 + (yPos * yFrame));
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
}