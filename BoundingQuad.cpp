#include "BoundingQuad.h"
#include "Point.h"
#include <iostream>
#include <iomanip>


BoundingQuad::BoundingQuad()
{
	points.resize(4);
	pointsN.resize(4);
	this->numberOfPoints = 4;
}

BoundingQuad::BoundingQuad(int numberOfPoints)
{
	points.resize(numberOfPoints);
	pointsN.resize(numberOfPoints);
	this->numberOfPoints = numberOfPoints;
}

BoundingQuad::BoundingQuad(Point& p1, Point& p2, Point& p3, Point& p4)
{
	points.resize(4);
	pointsN.resize(4);
	this->numberOfPoints = 4;
	pointsN[0] = p1;
	pointsN[1] = p2;
	pointsN[2] = p3;
	pointsN[3] = p4;
}

BoundingQuad::~BoundingQuad()
{
}

int BoundingQuad::getSize()
{
	return this->numberOfPoints;
}

void BoundingQuad::printBoxDetails()
{
	for (unsigned int i = 0; i < 4; i++)
	{
		std::cout <<std::setprecision(12) << "Point " << i << ": " << "x: " << pointsN[i].pointX << " y: " << pointsN[i].pointY << std::endl;
	}
	std::cout << "\n";
}

double BoundingQuad::getHalfWidth()
{
	return (pointsN[1].pointX - pointsN[0].pointX) / 2;
}

double BoundingQuad::getHalfHeight()
{
	return (pointsN[2].pointY - pointsN[1].pointY) / 2;
}

Point BoundingQuad::getCenter()
{
	Point result(pointsN[1].pointX - pointsN[0].pointX, pointsN[2].pointY - pointsN[1].pointY);
	return result;
}

void BoundingQuad::getMinMax(double* xMin, double* xMax, double* yMin, double* yMax)
{
	double xS = 0, xL = 0, yS = 0, yL = 0;
	xS = pointsN[0].pointX;
	xL = pointsN[0].pointX;
	yS = pointsN[0].pointY;
	yL = pointsN[0].pointY;

	for (int i = 1; i < 4; i++)
	{
		if (pointsN[i].pointX < xS)
		{
			xS = pointsN[i].pointX;
		}
		if (pointsN[i].pointX > xL)
		{
			xL = pointsN[i].pointX;
		}
		if (pointsN[i].pointY < yS)
		{
			yS = pointsN[i].pointY;
		}
		if (pointsN[i].pointY > yL)
		{
			yL = pointsN[i].pointY;
		}
	}
	*xMin = xS;
	*xMax = xL;
	*yMin = yS;
	*yMax = yL;
}

