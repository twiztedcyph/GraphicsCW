//
// The structure of the Graphics 1 OpenGL template is explained in README.txt
//

#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#include "SOIL.h"

#include "OpenGLApplication.h"			// Needed for OpenGLApplication method calls
#include "LevelThreeComplete.h"



LevelThreeComplete::LevelThreeComplete(OpenGLApplication *app)
: Activity(app)
{
}


void LevelThreeComplete::initialise()
{
	// Initialise the activity; called at application start up

	// Load the start screen image as a texture using the SOIL library
	textureID = SOIL_load_OGL_texture("sprites/lvlThreeComplete.png",			// filename
		SOIL_LOAD_AUTO,													// 
		SOIL_CREATE_NEW_ID,												// ask SOIL to create a new OpenGL texture ID for us
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);						// generate Mipmaps and invert Y
}


void LevelThreeComplete::shutdown()
{
	// Shutdown the activity; called at application finish

	// Delete the texture
	glDeleteTextures(1, &textureID);
}


/*
*
* ACTIVITY METHODS
* Put your application/game code here
*
*/
void LevelThreeComplete::onSwitchIn()
{
	// Activity switched in

	glClearColor(0.0, 0.0, 0.0, 0.0);						//sets the clear colour to black
}

void LevelThreeComplete::onReshape(int width, int height)
{
	// Screen resized
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	double aspect = app->getAspectRatio();
	gluOrtho2D(-aspect, aspect, -1.0, 1.0);				// set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void LevelThreeComplete::render()
{
	// OpenGL render calls go in this method

	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Identity matrix
	glLoadIdentity();

	// Bind our start screen texture to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex2f(-1.35, -1);

	glTexCoord2f(1, 0);
	glVertex2f(1.35, -1);

	glTexCoord2f(1, 1);
	glVertex2f(1.35, 1);

	glTexCoord2f(0, 1);
	glVertex2f(-1.35, 1);
	glEnd();

	// Disable 2D texturing
	glDisable(GL_TEXTURE_2D);

	glFlush();
}



void LevelThreeComplete::onKeyUp(int key)										// Called when key released
{
	// Key released

	// Exit the start screen when the SPACE key is released, NOT pressed
	// That way the next activity starts with the space key NOT pressed
	if (key == ' ')
	{
		app->setCurrentActivity(app->endScreen);
	}
	if (key == 'y')
	{

	}
}
