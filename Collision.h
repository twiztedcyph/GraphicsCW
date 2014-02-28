#pragma once
#include "BoundingQuad.h"

class Collision
{
public:
	Collision();
	~Collision();
	bool checkCollision(BoundingQuad* boxOne, BoundingQuad* boxTwo);

	bool checkCollision(BoundingQuad* boxOne, Point* point, double radius);

	bool checkCollision(Point* pointOne, double radiusOne, Point* pointTwo, double radiusTwo);

	bool hasLineOfSight(Point& lineStart, Point& lineEnd, BoundingQuad& lineBox, BoundingQuad& wallBox, Point& wallPoint, double checkDistanceSquared);

	bool foundSepAxis(Point& axis, BoundingQuad boxA, BoundingQuad boxB);

	bool isIntersect(BoundingQuad boxA, Point aPos, BoundingQuad boxB, Point bPos, Point& minTransDist);

	bool isIntersect(BoundingQuad boxA, Point aPos, BoundingQuad boxB, Point bPos, double checkDistanceSquared,Point& minTransDist);

	void getMinMax(Point axis, BoundingQuad box, double& min, double& max);

	Point getMinTransDist(Point* pushVectors, int numOfVectors);
};

