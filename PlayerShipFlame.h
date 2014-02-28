#pragma once
class PlayerShipFlame
{
private:
	double tick;
	double flameX, flameY, flameRot;
	int frame;
	GLfloat tPos;
	GLuint flameTextureID;
public:
	PlayerShipFlame();
	~PlayerShipFlame();

	void setImage(GLuint* flameTextureID);
	void updateFrame(double deltaT, double playerX, double playerY, double playerRotation);
	void renderPlayerShipFlame(double flameSize);
};

