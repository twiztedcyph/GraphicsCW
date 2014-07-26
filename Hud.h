#pragma once
#include <string>
#include <sstream>
#include "PlayerShip.h"

class Hud
{
private:
	PlayerShip * playerShip;
	double aspectRatio;
	HFONT font, oldFont;
	GLuint* ammoTextID, *hpTextID, *livesTextID, *shipIcon, *bulletIcon, *collectIcon;
	HDC hDC;
	double xFrame;
	double yFrame;
	double freq;
	int xPos, yPos;
public:
	Hud();
	~Hud();
	GLvoid init(GLuint& ammoTextID, GLuint& hpTextID, GLuint& livesTextID, GLuint& shipIcon, GLuint& bulletIcon, GLuint& collect);
	GLvoid shutDown();
	void setPlayer(PlayerShip& playerShip);
	void updateHud(double deltaT);

	void renderHud();
};

