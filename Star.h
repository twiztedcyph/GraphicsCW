#pragma once
class Star
{
private:
	double xPos, yPos, yVel, xVel;
	int size;
public:
	Star();
	Star(double x, double y, double yVel, double xVel, int size);
	~Star();

	void  set(double x, double y, double yVel, double xVel, int size);
	
	double getXPos();
	double getYPos();

	void setXPos(double x);
	void setYPos(double y);
	void move(double deltaT, double playerDx, double playerDy, double playerSpeed);
	void update(double camY, double camX);
	void draw();
};

