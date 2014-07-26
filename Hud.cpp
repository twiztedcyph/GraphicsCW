#include <windows.h>
#include <iostream>
#include "Hud.h"

// Header File For The OpenGL32 Library
#include <gl\gl.h>
// Header File For The GLu32 Library
#include <gl\glu.h>


#define VIEW_SIZE 30.0

Hud::Hud()
{
	
}

Hud::~Hud()
{
}


void Hud::setPlayer(PlayerShip& playerShip)
{
	this->playerShip = &playerShip;
}


GLvoid Hud::init(GLuint& ammoTextID, GLuint& hpTextID, GLuint& livesTextID, GLuint& shipIcon, GLuint& bulletIcon, GLuint& collect)
{
	this->ammoTextID = &ammoTextID;
	this->hpTextID = &hpTextID;
	this->livesTextID = &livesTextID;
	this->shipIcon = &shipIcon;
	this->bulletIcon = &bulletIcon;
	this->collectIcon = &collect;
	this->xFrame = 1.0 / 16;
	this->yFrame = 1.0 / 5;
	this->xPos = 0;
	this->yPos = 4;
	this->freq = 0;
}

GLvoid Hud::shutDown()
{
	//glDeleteLists(base, 96);
}

void Hud::updateHud(double deltaT)
{
	freq += (1 * deltaT);
	if (freq > 2.5)
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

void Hud::renderHud()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-VIEW_SIZE*0.5*aspectRatio, VIEW_SIZE*0.5*aspectRatio, -VIEW_SIZE*0.5, VIEW_SIZE*0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBindTexture(GL_TEXTURE_2D, *this->hpTextID);
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
			glColor3f(1.0f, 1.0f, 1.0f);
			glTexCoord2f(0, 0);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 17, (VIEW_SIZE * 0.5 * aspectRatio) - 14);
			glTexCoord2f(1, 0);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 14);
			glTexCoord2f(1, 1);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 12);
			glTexCoord2f(0, 1);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 17, (VIEW_SIZE * 0.5 * aspectRatio) - 12);
		glEnd();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	glColor3f((100 - playerShip->getPlayerHP()) / 100, playerShip->getPlayerHP() / 100, 0.0f);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12, (VIEW_SIZE * 0.5 * aspectRatio) - 13.8);
		glVertex2f(((VIEW_SIZE * 0.5 * aspectRatio) - 12) + playerShip->getPlayerHP() / 5, (VIEW_SIZE * 0.5 * aspectRatio) - 13.8);
		glVertex2f(((VIEW_SIZE * 0.5 * aspectRatio) - 12) + playerShip->getPlayerHP() / 5, (VIEW_SIZE * 0.5 * aspectRatio) - 12.2);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12, (VIEW_SIZE * 0.5 * aspectRatio) - 12.2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *this->livesTextID);
	glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 17, (VIEW_SIZE * 0.5 * aspectRatio) - 12);
			glTexCoord2f(1, 0);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 12);
			glTexCoord2f(1, 1);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 10);
			glTexCoord2f(0, 1);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 17, (VIEW_SIZE * 0.5 * aspectRatio) - 10);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, *this->shipIcon);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (unsigned i = 0; i < playerShip->getPlayerLives(); i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 12);
		glTexCoord2f(1, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 11 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 12);
		glTexCoord2f(1, 1);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 11 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 10);
		glTexCoord2f(0, 1);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, *this->ammoTextID);
	glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 17, (VIEW_SIZE * 0.5 * aspectRatio) - 10);
			glTexCoord2f(1, 0);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 10);
			glTexCoord2f(1, 1);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 8);
			glTexCoord2f(0, 1);
			glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 17, (VIEW_SIZE * 0.5 * aspectRatio) - 8);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, *this->bulletIcon);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (unsigned i = 0; i < playerShip->ammoLeft; i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 9.6);
		glTexCoord2f(1, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 11.5 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 9.6);
		glTexCoord2f(1, 1);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 11.5 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 8.4);
		glTexCoord2f(0, 1);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 8.4);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, *this->bulletIcon);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (unsigned i = 0; i < playerShip->ammoLeft; i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 9.6);
		glTexCoord2f(1, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 11.5 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 9.6);
		glTexCoord2f(1, 1);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 11.5 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 8.4);
		glTexCoord2f(0, 1);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i, (VIEW_SIZE * 0.5 * aspectRatio) - 8.4);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, *this->collectIcon);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glTexCoord2f(0 + (xPos * xFrame), 0 + (yPos * yFrame));
	glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 15, (VIEW_SIZE * 0.5 * aspectRatio) - 6);
	glTexCoord2f(xFrame + (xPos * xFrame), 0 + (yPos * yFrame));
	glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 6);
	glTexCoord2f(xFrame + (xPos * xFrame), yFrame + (yPos * yFrame));
	glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 13, (VIEW_SIZE * 0.5 * aspectRatio) - 8);
	glTexCoord2f(0 + (xPos * xFrame), yFrame + (yPos * yFrame));
	glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 15, (VIEW_SIZE * 0.5 * aspectRatio) - 8);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, *this->collectIcon);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (unsigned i = 0; i < playerShip->collected; i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 6);
		glTexCoord2f(xFrame, 0);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 10 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 6);
		glTexCoord2f(xFrame, yFrame);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 10 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 8);
		glTexCoord2f(0, yFrame);
		glVertex2f((VIEW_SIZE * 0.5 * aspectRatio) - 12 + i * 2, (VIEW_SIZE * 0.5 * aspectRatio) - 8);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
	glPopMatrix();

}