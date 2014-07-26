#include <windows.h>		// Header File For Windows.
#include <gl\gl.h>			// Header File For The OpenGL32 Library.
#include <gl\glu.h>			// Header File For The GLu32 Library.
#include <vector>			// Header file for vector library.
#include "Star.h"
#include "StarField.h"
#include "RandomGen.h"
#include <iostream>
#include "PlayerShip.h"

//Star speed doubles at each next stage for paralax effect.
#define SMALL_STAR_PARALLAX_SPEED 0.01
#define MED_STAR_PARALLAX_SPEED 0.02
#define LARGE_STAR_PARALLAX_SPEED 0.04

//Star brightness selector.
#define LOW_STAR_BRIGHTNESS 1
#define MED_STAR_BRIGHTNESS 2
#define HIGH_STAR_BRIGHTNESS 3

std::vector<Star> starField;

StarField::StarField(int sml, int med, int lrg, PlayerShip* player)
{
	this->smallCount = sml;
	this->mediumCount = med;
	this->largeCount = lrg;
	this->playerRef = player;
}

StarField::StarField()
{
	this->smallCount = 0;
	this->mediumCount = 0;
	this->largeCount = 0;
	this->playerRef = nullptr;
}

StarField::~StarField(){}

void StarField::clear()
{
	starField.clear();
}

void StarField::initialise()
{
	if (starField.empty())
	{
		for (int i = 0; i < smallCount; i++)
		{
			if (i < mediumCount)
			{
				Star star(RandomGen().getRand(playerRef->getPlayerX() + 30,
					playerRef->getPlayerX() - 30),
					RandomGen().getRand(playerRef->getPlayerY() + 18,
					playerRef->getPlayerY() - 18),
					MED_STAR_PARALLAX_SPEED,
					MED_STAR_PARALLAX_SPEED,
					MED_STAR_BRIGHTNESS);
				starField.push_back(star);
			}
			if (i < largeCount)
			{
				Star star(RandomGen().getRand(playerRef->getPlayerX() + 30,
					playerRef->getPlayerX() - 30),
					RandomGen().getRand(playerRef->getPlayerY() + 18,
					playerRef->getPlayerY() - 18),
					LARGE_STAR_PARALLAX_SPEED,
					LARGE_STAR_PARALLAX_SPEED,
					HIGH_STAR_BRIGHTNESS);
				starField.push_back(star);
			}
			Star star(RandomGen().getRand(playerRef->getPlayerX() + 30,
				playerRef->getPlayerX() - 30),
				RandomGen().getRand(playerRef->getPlayerY() + 18,
				playerRef->getPlayerY() - 18),
				SMALL_STAR_PARALLAX_SPEED,
				SMALL_STAR_PARALLAX_SPEED,
				LOW_STAR_BRIGHTNESS);
			starField.push_back(star);
		}
	}
	else
	{
		starField.clear();
		initialise();
	}
}

void StarField::initialise(double xPos, double yPos)
{
	if (starField.empty())
	{
		for (int i = 0; i < smallCount; i++)
		{
			if (i < mediumCount)
			{
				Star star(RandomGen().getRand(xPos + 30,
					xPos - 30),
					RandomGen().getRand(yPos + 18,
					yPos - 18),
					MED_STAR_PARALLAX_SPEED,
					MED_STAR_PARALLAX_SPEED,
					MED_STAR_BRIGHTNESS);
				starField.push_back(star);
			}
			if (i < largeCount)
			{
				Star star(RandomGen().getRand(xPos + 30,
					xPos - 30),
					RandomGen().getRand(yPos + 18,
					yPos - 18),
					LARGE_STAR_PARALLAX_SPEED,
					LARGE_STAR_PARALLAX_SPEED,
					HIGH_STAR_BRIGHTNESS);
				starField.push_back(star);
			}
			Star star(RandomGen().getRand(xPos + 30,
				xPos - 30),
				RandomGen().getRand(yPos + 18,
				yPos - 18),
				SMALL_STAR_PARALLAX_SPEED,
				SMALL_STAR_PARALLAX_SPEED,
				LOW_STAR_BRIGHTNESS);
			starField.push_back(star);
		}
	}
	else
	{
		starField.clear();
		initialise();
	}
}

void StarField::drawAll()
{
	for (unsigned i = 0; i < starField.size(); i++)
	{
		starField[i].draw();
	}
}

void StarField::updateAll(double camY, double camX)
{
	for (unsigned i = 0; i < starField.size(); i++)
	{
		starField[i].update(camY, camX);
	}
}

void StarField::move(double deltaT)
{
	for (unsigned i = 0; i < starField.size(); i++)
	{
		starField[i].move(deltaT, playerRef->dx, playerRef->dy, playerRef->getPlayerSpeed());
	}
}

int StarField::size()
{
	return starField.size();
}
