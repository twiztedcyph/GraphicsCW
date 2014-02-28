#pragma once
#include <windows.h>		// Header File For Windows.
#include <gl\gl.h>			// Header File For The OpenGL32 Library.
#include <gl\glu.h>			// Header File For The GLu32 Library.
#include "Asteroid.h"
#include <vector>
#include "CompShip.h"
#include "Collectable.h"
#include "CollectableList.h"

class EnemyList;

class Map
{
private:
	double xStart, yStart;
	GLuint* asteroidTextureId, * enemyTextureID, * collectableTextureID;
	EnemyList* enemyList;
	CollectableList* collectableList;
public:
	std::vector<Asteroid> asteroidField;
	
	Map();
	
	Map(double xStart, double yStart, EnemyList* enemyList, CollectableList* collectableList, GLuint* asteroidTextureID, GLuint* enemyTextureID, GLuint* collectableTextureID);
	
	~Map();
	
	void drawField();

	void updateField(double deltaT);
	
	void addAsteroid(Asteroid newAsteroid);
	
	void makeField();
};

