//
// The structure of the Graphics 1 OpenGL template is explained in README.txt
//

#include <stdio.h>

#include <Windows.h>

#include "SOIL.h"

#include "StartScreenActivity.h"
#include "GameActivity.h"
#include "GameActivityTwo.h"
#include "GameActivityThree.h"
#include "EndScreenActivity.h"
#include "InstructionActivity.h"
#include "OpenGLApplication.h"
#include "LevelOneComplete.h"
#include "LevelTwoComplete.h"
#include "LevelThreeComplete.h"

OpenGLApplication::OpenGLApplication()
{
	// Sensible defaults to start with
	screenWidth = 800;
	screenHeight = 600;

	currentActivity = NULL;

	finished = false;
}


// Getters for input state and screen size
InputState & OpenGLApplication::getInputState()
{
	return inputState;
}

const InputState & OpenGLApplication::getInputState() const
{
	return inputState;
}

int OpenGLApplication::getScreenWidth() const
{
	return screenWidth;
}

int OpenGLApplication::getScreenHeight() const
{
	return screenHeight;
}

double OpenGLApplication::getAspectRatio() const
{
	return (double)screenWidth / (double)screenHeight;
}



//  Activity
Activity * OpenGLApplication::getCurrentActivity()
{
	return currentActivity;
}

void OpenGLApplication::setCurrentActivity(Activity *a)
{
	if (currentActivity != NULL)
	{
		currentActivity->onSwitchOut();
	}
	
	currentActivity = a;

	if (currentActivity != NULL)
	{
		currentActivity->onSwitchIn();
		currentActivity->onReshape(screenWidth, screenHeight);
	}
}




// Initialise application
void OpenGLApplication::initialise()
{
	startScreen = new StartScreenActivity(this);
	instructionScreen = new InstructionActivity(this);
	gameOne = new GameActivity(this);
	gameTwo = new GameActivityTwo(this);
	gameThree = new GameActivityThree(this);
	endScreen = new EndScreenActivity(this);
	levelOneComplete = new LevelOneComplete(this);
	levelTwoComplete = new LevelTwoComplete(this);
	levelThreeComplete = new LevelThreeComplete(this);

	startScreen->initialise();
	instructionScreen->initialise();
	levelOneComplete->initialise();
	levelTwoComplete->initialise();
	levelThreeComplete->initialise();
	gameOne->initialise();
	
	endScreen->initialise();
	setCurrentActivity(startScreen);
}

// Shutdown application
void OpenGLApplication::shutdown()
{
	startScreen->shutdown();
	levelOneComplete->shutdown();
	levelTwoComplete->shutdown();
	levelThreeComplete->shutdown();
	gameOne->shutdown();
	gameTwo->shutdown();
	gameThree->shutdown();
	endScreen->shutdown();

	delete startScreen;
	delete levelOneComplete;
	delete levelTwoComplete;
	delete levelThreeComplete;
	delete instructionScreen;
	delete gameOne;
	delete gameTwo;
	delete gameThree;
	delete endScreen;

	startScreen = NULL;
	levelOneComplete = NULL;
	levelTwoComplete = NULL;
	levelThreeComplete = NULL;
	instructionScreen = NULL;
	gameOne = NULL;
	gameTwo = NULL;
	gameThree = NULL;
	endScreen = NULL;
}

void OpenGLApplication::closeOne()
{
	gameOne->shutdown();
	delete gameOne;
	gameOne = NULL;

	gameOne = new GameActivity(this);
}

void OpenGLApplication::closeTwo()
{
	gameTwo->shutdown();
	delete gameTwo;
	gameTwo = NULL;

	gameTwo = new GameActivityTwo(this);
}

void OpenGLApplication::closeThree()
{
	gameThree->shutdown();
	delete gameThree;
	gameThree = NULL;

	gameThree = new GameActivityThree(this);
}

void OpenGLApplication::finish()
{
	finished = true;
}

bool OpenGLApplication::isApplicationFinished()
{
	return finished;
}





/*
*
* The methods below are invoked by the Win32 code to inform the application of various events
*
* Mainly, they just pass on events to the current activity.
*
* You don't need to add to these methods.
*
*/

void OpenGLApplication::handleReshape(int width, int height)
{
	// You DO NOT need to write any additional code here...

	screenWidth = width;
	screenHeight = height;

	if (currentActivity != NULL)
	{
		currentActivity->onReshape(width, height);
	}
}

void OpenGLApplication::handleUpdate(double deltaT, double prevDeltaT)
{
	// You DO NOT need to write any additional code here...

	// Just call update
	if (currentActivity != NULL)
	{
		currentActivity->update(deltaT, prevDeltaT);
	}
}

void OpenGLApplication::handleRender()
{
	// You DO NOT need to write any additional code here...

	if (currentActivity != NULL)
	{
		currentActivity->render();
	}
}


void OpenGLApplication::handleMouseDown(int button, int mouseX, int mouseY)
{
	// You DO NOT need to write any additional code here...

	// Tell inputState, then invoke the event method
	inputState.handleMouseDown(button, mouseX, mouseY);
	if (currentActivity != NULL)
	{
		currentActivity->onMouseDown(button, mouseX, mouseY);
	}
}

void OpenGLApplication::handleMouseUp(int button, int mouseX, int mouseY)
{
	// You DO NOT need to write any additional code here...

	// Tell inputState, then invoke the event method
	inputState.handleMouseUp(button, mouseX, mouseY);
	if (currentActivity != NULL)
	{
		currentActivity->onMouseUp(button, mouseX, mouseY);
	}
}

void OpenGLApplication::handleMouseMove(int mouseX, int mouseY)
{
	// You DO NOT need to write any additional code here...

	// Tell inputState, then invoke the event method
	inputState.handleMouseMove(mouseX, mouseY);
	if (currentActivity != NULL)
	{
		currentActivity->onMouseMove(mouseX, mouseY);
	}
}

void OpenGLApplication::handleKeyDown(int key)
{
	// You DO NOT need to write any additional code here...

	// Tell inputState, then invoke the event method
	inputState.handleKeyDown(key);
	if (currentActivity != NULL)
	{
		currentActivity->onKeyDown(key);
	}

	// Finish if the escape key has been pressed
	if (key == VK_ESCAPE)
	{
		finish();
	}
}

void OpenGLApplication::handleKeyUp(int key)
{
	// You DO NOT need to write any additional code here...

	// Tell inputState, then invoke the event method
	inputState.handleKeyUp(key);
	if (currentActivity != NULL)
	{
		currentActivity->onKeyUp(key);
	}
}

