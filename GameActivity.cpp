//
// The structure of the Graphics 1 OpenGL template is explained in README.txt
//

/*
GameActivity implementation


The comments in the file Activity.cpp give a little more info about each method

This activity is where the main game logic goes.
Most of your game code will go here
*/

// Header File For Windows
#include <windows.h>

// Header File For The OpenGL32 Library
#include <gl\gl.h>

// Header File For The GLu32 Library
#include <gl\glu.h>

//Image loading library.
#include "SOIL.h"

// Needed to access member functions and variables from OpenGLApplication
#include "OpenGLApplication.h"
#include "GameActivity.h"
#include "RandomGen.h"
#include "Bullet.h"
#include "PlayerProjectiles.h"
#include "PlayerShip.h"
#include "PlayerShipFlame.h"
#include "StarField.h"
#include "EnemyList.h"
#include "CompShip.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Asteroid.h"
#include "EnemyProjectiles.h"
#include <mmsystem.h>
#include "Map.h"
#include "CollectableList.h"

//for cout and endl.
using namespace std;

// The height of the view in WORLD SPACE
#define VIEW_SIZE 30.0

//Camera a player movement speed.
#define CAMERA_MOVEMENT_SPEED 10.0
#define PLAYER_MOVEMENT_SPEED 10.0
#define PLAYER_LEFT_BOUNDARY -5
#define PLAYER_RIGHT_BOUNDARY 5

//Initialise the bullet storage class for players and enemies.
PlayerProjectiles bullets;

CollectableList collectableList;

//Initialise the player's ship.
PlayerShip playerShip(11.2, -88.6);

//Initialise the animated player's ship flame.
PlayerShipFlame playerShipFlame;

StarField starField(200, 80, 20, &playerShip);

EnemyList enemyList;

Map map;


GameActivity::GameActivity(OpenGLApplication *app)
: Activity(app)		// Call super constructor
{
	// Initialse camera and player positions to be a the origin
	camX = camY = 0.0;
	//gameSpeed = 2.2;
}

/*
*
* ACTIVITY METHODS
* Put your application/game code here
*
*/
void GameActivity::initialise()
{
	//Seed the psuedo random number generator.
	srand(time(0));
	// Initialise the activity; called at application start up

	// Load images using the SOIL library
	enemyTextureID = SOIL_load_OGL_texture("sprites/smlEnemy.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	explosionTextureID = SOIL_load_OGL_texture("sprites/explosionTwo.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	playerTextureID = SOIL_load_OGL_texture("sprites/player.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	playerHitTextureID = SOIL_load_OGL_texture("sprites/player_hit.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	flameTextureID = SOIL_load_OGL_texture("sprites/flame.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	bulletTextureID = SOIL_load_OGL_texture("sprites/bSprite.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	ebulletTextureID = SOIL_load_OGL_texture("sprites/ebSprite.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	asteroidTextureID = SOIL_load_OGL_texture("sprites/asteroidtest.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	collectableTextureID = SOIL_load_OGL_texture("sprites/boxtest.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	playerShipFlame.setImage(&flameTextureID);
	playerShip.setImages(&playerTextureID, &playerHitTextureID);
	//Initialise the star fields.
	starField.initialise();
	//Set the enemyBullet texture.
	enemyList.setEnemyBulletTexture(&ebulletTextureID, &explosionTextureID);
	enemyList.setAsteroidList(&map);

	playerShip.setEnemyList(&enemyList);
	playerShip.setCollectableList(&collectableList);
	//PlaySound("sounds/bgOne.wav", NULL, SND_ASYNC);
	map = Map(0, 20, &enemyList, &collectableList, &asteroidTextureID, &enemyTextureID, &collectableTextureID);
	map.makeField();
	playerShip.setAsteroidList(&map);
	
}


void GameActivity::shutdown()
{
	// Delete loaded textures on exit.
	glDeleteTextures(1, &playerTextureID);
	glDeleteTextures(1, &playerHitTextureID);
	glDeleteTextures(1, &flameTextureID);
	glDeleteTextures(1, &bulletTextureID);
	glDeleteTextures(1, &asteroidTextureID);
	glDeleteTextures(1, &enemyTextureID);
	glDeleteTextures(1, &explosionTextureID);
}



void GameActivity::onSwitchIn()
{
	//Set the clear colour to black.
	glClearColor(0.0, 0.0, 0.0, 0.0);

}

void GameActivity::onReshape(int width, int height)
{
	// If you need to do anything when the screen is resized, do it here

	// EXAMPLE CODE
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	double aspect = app->getAspectRatio();
	// The height of the visible area is defined by VIEW_SIZE. Split it half each way around the origin, hence the *0.5
	// Take the aspect ratio into consideration when computing the width of the visible area
	gluOrtho2D(-VIEW_SIZE*0.5*aspect, VIEW_SIZE*0.5*aspect, -VIEW_SIZE*0.5, VIEW_SIZE*0.5);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void GameActivity::update(double deltaT, double prevDeltaT)
{
	// Update the application; if the current frame is frame number F, then the previous frame is F-1 and the one before that is F-2
	// deltaT is the time elapsed from frame F-1 to frame F, prevDeltaT is the time elapsed from F-2 to F-1

	// Update the simulation here
	// TRY NOT TO DO ANY RENDERING HERE
	// step the simulation forward by the amount of time specified by deltaT
	//
	// If you need to do different things depending on whether or not keys are pressed, etc,
	// get the member variable inputState and use its isKeyPressed(), getMouseX(), getMouseY() and isMouseButtonPressed() methods
	// to determine the state of the keys
	collectableList.removeCollectable();
	enemyList.remove();
	//Remove bullets off the screen from the bullet vector.
	bullets.remove(camY);

	//Update the player ship.
	playerShip.playerUpdate(deltaT);
	
	//Flame update
	playerShipFlame.updateFrame(deltaT, playerShip.getPlayerX(), playerShip.getPlayerY(), playerShip.getPlayerRot());
	
	//Update the camera y axis.
	camY = playerShip.getPlayerY();
	camX = playerShip.getPlayerX();
	
	//Update all bullets.
	bullets.updateAllBullets(deltaT);
	
	//Star updates. These will be separated out at some stage.
	starField.updateAll(camY, camX);
	starField.move(deltaT);
	collectableList.updateAllCollectables(deltaT);
	enemyList.checkCollisions(bullets);
	enemyList.updateAllEnemies(playerShip.getPlayerX(), playerShip.getPlayerY(), deltaT);
	map.updateField(deltaT);

	if (enemyList.getSize() < 0)
	{
		enemyList.spawnNewRandom(playerShip.getPlayerX(), playerShip.getPlayerY(), &enemyTextureID);
	}

	//Camera behaviour based on player's current position.
	if (playerShip.getPlayerX() < -5 && playerShip.getPlayerX() > -20)
	{
		if (camX > -5)
		{
			camX -= CAMERA_MOVEMENT_SPEED * deltaT;			
		}
	}
	else if (playerShip.getPlayerX() > 5 && playerShip.getPlayerX() < 20)
	{
		if (camX < 5)
		{
			camX += CAMERA_MOVEMENT_SPEED * deltaT;
		}
	}
	else if (playerShip.getPlayerX() >= -15 && playerShip.getPlayerX() <= 15)
	{
		if (camX < 0)
		{
			camX = playerShip.getPlayerX();
		}
		if (camX > 0)
		{
			camX = playerShip.getPlayerX();
		}
	}

	/*Manual camera control here.  This will not be available in the main game.*/
	if (inputState->isKeyPressed(VK_LEFT))
	{
		camX -= CAMERA_MOVEMENT_SPEED * deltaT;
	}
	if (inputState->isKeyPressed(VK_RIGHT))
	{
		camX += CAMERA_MOVEMENT_SPEED * deltaT;
	}
	if (inputState->isKeyPressed(VK_UP))
	{
		
	}
	if (inputState->isKeyPressed(VK_DOWN))
	{
		camY -= CAMERA_MOVEMENT_SPEED * deltaT;
	}

	// WASD player control.
	if (inputState->isKeyPressed('A'))
	{
		playerShip.playerRotateLeft(deltaT);
	}
	if (inputState->isKeyPressed('D'))
	{
		playerShip.playerRotateRight(deltaT);
	}
	if (inputState->isKeyPressed('W'))
	{
		playerShip.playerSpeedUp(deltaT);
	}
	if (inputState->isKeyPressed('S'))
	{
		playerShip.playerSpeedDown(deltaT);
	}
}

void GameActivity::render()
{
	// OpenGL render calls go in this method
	//
	// IMPORTANT:
	// DO NOT update the simulation (move objects, change their state in response to user input) in this method or methods
	// called by this method. These methods should ONLY render objects
	//

	// First:
	// set your projection matrix:
	// <here>

	// Second:
	// set your camera matrix:
	// <here>

	// Third:
	// Render your objects:
	// <here>


	// If you want to have any overlay/HUD/etc:
	// Set a projection matrix that does not scroll:
	// <here>

	// Now render your HUD:
	// <here>


	// EXAMPLE CODE:
	glClear(GL_COLOR_BUFFER_BIT);

	// Reset The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Use the negated camera position as a translation; effectively we move the world and the camera so that the camera is at 0,0,0
	glTranslated(-camX, -camY, 0.0);


	//Render stars. Move this out soon.	
	starField.drawAll();

	map.drawField();

	//Render bullets.
	bullets.drawAllBullets();
	
	//Render player.
	playerShip.playerDraw();
	
	collectableList.drawAllCollectables();

	//Render the flame for the player's ship.
	if (playerShip.getPlayerSpeed() > 0)
	{
		playerShipFlame.renderPlayerShipFlame(playerShip.getPlayerSpeed() / 10);
	}

	enemyList.drawAllEnemies();

	glFlush();
	glFinish();
}



void GameActivity::onMouseDown(int button, int mouseX, int mouseY)
{
	// This method will be invoked when a mouse button is pressed
	// button: 0=LEFT, 1=MIDDLE, 2=RIGHT
	// mouseX and mouseY: position
	if (button == 2)
	{
		CompShip newEnemy(0, playerShip.getPlayerY() + 23, &enemyTextureID);
		enemyList.addNewEnemy(newEnemy);
	}
	if (button == 0 && playerShip.isReadyToFire())
	{
		Bullet b(playerShip.getPlayerX(), playerShip.getPlayerY(), playerShip.getPlayerRot(), &bulletTextureID);
		bullets.add(b);
		PlaySound("sounds/laserShoot.wav", NULL, SND_ASYNC);
	}
}

void GameActivity::onMouseUp(int button, int mouseX, int mouseY)
{
	// This method will be invoked when a mouse button is released
	// button: 0=LEFT, 1=MIDDLE, 2=RIGHT
	// mouseX and mouseY: position
}

void GameActivity::onMouseMove(int mouseX, int mouseY)
{
	// This method will be invoked when the mouse is moved
	// mouseX and mouseY: position
}

void GameActivity::onKeyDown(int key)
{
	// This method will be invoked when a key is pressed
	if (key == VK_SPACE)
	{
		
	}
}

void GameActivity::onKeyUp(int key)  // Called when key released
{
	// Key released

	// Exit the start screen when the SPACE key is released, NOT pressed
	// That way the next activity starts with the space key NOT pressed
	if (key == VK_F1)
	{
		// F1; switch to end screen activity
		app->setCurrentActivity(app->endScreen);
	}
	if (key == VK_SPACE)
	{
		cout << playerShip.getPlayerX() << "\t" << playerShip.getPlayerY() << endl;
	}
}
