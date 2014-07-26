// Ensure that this file can only be included once
#pragma once

#include "Activity.h"
#include "PlayerProjectiles.h"
#include "CollectableList.h"
#include "PlayerShip.h"
#include "PlayerShipFlame.h"
#include "StarField.h"
#include "EnemyList.h"
#include "CompShip.h"
#include "Asteroid.h"
#include "EnemyProjectiles.h"
#include "Map.h"
#include "Hud.h"

class GameActivity : public Activity
{
private:
	// GAME activity variables go here
	//Initialise the bullet storage class for players and enemies.
	PlayerProjectiles bullets;

	CollectableList collectableList;

	//Initialise the player's ship.
	PlayerShip playerShip;

	//Initialise the animated player's ship flame.
	PlayerShipFlame playerShipFlame;

	StarField starField;

	EnemyList enemyList;

	Map map;

	//Hud hud;
	// Camera position
	double camX, camY;
	double screenWidth, screenHeight;
	bool pause;
	//Sprite textures
	GLuint playerTextureID, starTextureID, ebulletTextureID;
	GLuint flameTextureID, bulletTextureID, enemyTextureID;
	GLuint asteroidTextureID, explosionTextureID, playerHitTextureID;
	GLuint collectableTextureID, ammoTextID, hpTextID, livesTextID;

	// The speed which the game will enforce the player move through the world.
	double gameSpeed;

public:
	GameActivity(OpenGLApplication *app);

	/*
	*
	* GAME activity methods
	* You should put your game code in the implementations of these methods
	* See GameActivity.cpp
	*
	*/
	virtual void initialise();											// Called on application start up
	virtual void initStar();
	virtual void shutdown();											// Called on application shut down

	virtual void onSwitchIn();											// Activity switch in; called when the activity changes and this one switches in
	virtual void onSwitchOut();
	virtual void onReshape(int width, int height);						// called when the window is resized
	virtual void update(double deltaT, double prevDeltaT);				// Update the application; if the current frame is frame number F, then the previous frame is F-1 and the one before that is F-2
																		// deltaT is the time elapsed from frame F-1 to frame F, prevDeltaT is the time elapsed from F-2 to F-1
	virtual void render();												// Render function


	virtual void onMouseDown(int button, int mouseX, int mouseY);		// Called when mouse button pressed
	virtual void onMouseUp(int button, int mouseX, int mouseY);			// Called when mouse button released
	virtual void onMouseMove(int mouseX, int mouseY);					// Called when mouse moved
	virtual void onKeyDown(int key);									// Called when key pressed
	virtual void onKeyUp(int key);										// Called when key released

	void renderPlayer();
	void renderFlame();
	// Drawing a grid in the background; useful for debugging
	void renderDebugGrid(float left, float bottom, float width, float height, int hSegments, int vSegments);

	void initLargeStar(int density);

	void updateLargeStar(double deltaT);

	void renderLargeStar();
	
	void initMedStar(int density);

	void updateMedStar(double deltaT);

	void renderMedStar();

	void initSmallStar(int density);

	void updateSmallStar(double deltaT);

	void renderSmallStar();
};