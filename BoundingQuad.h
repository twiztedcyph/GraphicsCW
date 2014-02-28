#pragma once
#include "Point.h"

class BoundingQuad
{
private:
	int numberOfPoints;
public:
	Point* points;
	Point* pointsN;
	BoundingQuad();
	BoundingQuad(int numberOfPoints);
	BoundingQuad(Point& p1, Point& p2, Point& p3, Point& p4);
	~BoundingQuad();

	void printBoxDetails();
	void getMinMax(double* xMin, double* xMax, double* yMin, double* yMax);
	double getHalfWidth();
	double getHalfHeight();
	int getSize();
	Point getCenter();
};

