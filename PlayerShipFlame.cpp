#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "SOIL.h"
#include "OpenGLApplication.h"
#include "playerShipFlame.h"
#include <iostream>


PlayerShipFlame::PlayerShipFlame()
{
	flameX = 0;
	flameY = 0;
	flameRot = 0;
	tick = 0.0;
	frame = 0;
	tPos = 1.0 / 4;
}


PlayerShipFlame::~PlayerShipFlame()
{
}

void PlayerShipFlame::setImage(GLuint* flameTextureID)
{
	this->flameTextureID = *flameTextureID;
}

void PlayerShipFlame::updateFrame(double deltaT, double playerX, double playerY, double playerRotation)
{
	flameX = playerX;
	flameY = playerY;
	flameRot = playerRotation;
	//Timing mechanism for flame animation.
	tick += 1 * deltaT;
	if (tick > 0.05)
	{
		frame = (frame + 1) % 4;
		tick = 0.0;
	}
}

void PlayerShipFlame::renderPlayerShipFlame(double flameSize)
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Using open gl rotate and translate as the flame is not included in the collision detection.
	glTranslatef(flameX, flameY, 0.0);
	glRotatef(flameRot, 0.0, 0.0, 1.0);
	glTranslatef(0.021, -2.2, 0.0);

	glBindTexture(GL_TEXTURE_2D, flameTextureID);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0, 1.0 / 4 + (frame * tPos));
	glVertex2f(flameSize * -0.13, flameSize * -0.13);
	glTexCoord2f(0, 0 + (frame * tPos));
	glVertex2f(flameSize * -0.13, flameSize * 0.13);
	glTexCoord2f(1.0 / 4, 0 + (frame * tPos));
	glVertex2f(flameSize * 0.13, flameSize * 0.13);
	glTexCoord2f(1.0 / 4, 1.0 / 4 + (frame * tPos));
	glVertex2f(flameSize * 0.13, flameSize * -0.13);

	glEnd();

	// Enable 2D texturing
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}
