#include <math.h>

#include "Collision.h"
#include "BoundingQuad.h"
#include "Point.h"
#include <iostream>
#include <math.h>


Collision::Collision()
{
}


Collision::~Collision()
{
}


bool Collision::checkCollision(BoundingQuad& boxOne, Point& point, double radius)
{
	for (size_t i = 0; i < boxOne.getSize(); i++)
	{
		double xDif = boxOne.pointsN[i].pointX - point.pointX;
		double yDif = boxOne.pointsN[i].pointY - point.pointY;
		if ((radius * radius) >= ((xDif * xDif) + (yDif * yDif)) + 0.2)
		{
			return true;
		}

	}
	return false;
}

bool Collision::checkCollision(Point& pointOne, double radiusOne, Point& pointTwo, double radiusTwo)
{
	double xDiff = pointTwo.pointX - pointOne.pointX;
	double yDiff = pointTwo.pointY - pointOne.pointY;
	double tRadius = radiusOne + radiusTwo;

	if ((tRadius * tRadius) >= (xDiff * xDiff) + (yDiff * yDiff))
	{
		return true;
	}
	return false;
}

bool Collision::hasLineOfSight(Point& lineStart, Point& lineEnd, BoundingQuad& lineBox, BoundingQuad& wallBox, Point& wallPoint ,double checkDistanceSquared)
{
	
		for (unsigned int i = 0, j = lineBox.getSize() - 1; i < lineBox.getSize(); j = i, i++)
		{
			Point axisA = lineBox.pointsN[i].getEdgeNormal(&lineBox.pointsN[j]);
			if (foundSepAxis(axisA, lineBox, wallBox))
			{
				return true;
			}
		}

		for (unsigned int i = 0, j = wallBox.getSize() - 1; i < wallBox.getSize(); j = i, i++)
		{
			Point axisB = wallBox.pointsN[i].getEdgeNormal(&wallBox.pointsN[j]);
			if (foundSepAxis(axisB, lineBox, wallBox))
			{
				return true;
			}
		}
		return false;
	
}

void Collision::getMinMax(Point axis, BoundingQuad &box, double& min, double& max)
{
	double dotProd = axis.getDotProd(&box.pointsN[0]);

	min = max = dotProd;

	for (unsigned int i = 0; i < box.getSize(); i++)
	{
		dotProd = axis.getDotProd(&box.pointsN[i]);
		if (dotProd < min)
		{
			min = dotProd;
		}
		else if (dotProd > max)
		{
			max = dotProd;
		}
	}
}

bool Collision::foundSepAxis(Point& axis, BoundingQuad &boxA, BoundingQuad &boxB)
{
	double boxAMin, boxBMin, boxAMax, boxBMax;

	getMinMax(axis, boxA, boxAMin, boxAMax);
	getMinMax(axis, boxB, boxBMin, boxBMax);

	if ((boxAMin > boxBMax) || (boxBMin > boxAMax))
	{
		return true;
	}
	
	double d1 = boxAMax - boxBMin;
	double d2 = boxBMax - boxAMin;

	double depthTimesAxisLength = (d1 < d2) ? d1 : d2;

	double axisSqrLength = axis.getDotProd(&axis);

	//double axisLengthRecip = 1.0 / sqrt(axisSqrLength);

	//double d3 = depth * axisLengthRecip;

	//axis = Point(axis.pointX * axisLengthRecip * d3, axis.pointY * axisLengthRecip * d3);

	double axisSqrLengthRecip = 1.0 / axisSqrLength;
	axis = Point(axis.pointX * depthTimesAxisLength * axisSqrLengthRecip,
		axis.pointY * depthTimesAxisLength * axisSqrLengthRecip);

	return false;
}

bool Collision::isIntersect(BoundingQuad &boxA, Point aPos, BoundingQuad &boxB, Point bPos, double checkDistanceSquared, Point& minTransVec)
{
	double xDiff = aPos.pointX - bPos.pointX;
	double yDiff = aPos.pointY - bPos.pointY;
	if ((xDiff * xDiff) + (yDiff * yDiff) < checkDistanceSquared)
	{

		Point points[32];
		int numOfAxis = 0;
		for (unsigned int i = 0, j = boxA.getSize() - 1; i < boxA.getSize(); j = i, i++)
		{
			Point axisA = boxA.pointsN[i].getEdgeNormal(&boxA.pointsN[j]);
			if (foundSepAxis(axisA, boxA, boxB))
			{
				return false;
			}
			else
			{
				points[numOfAxis++] = axisA;
			}
		}

		for (unsigned int i = 0, j = boxB.getSize() - 1; i < boxB.getSize(); j = i, i++)
		{
			Point axisB = boxB.pointsN[i].getEdgeNormal(&boxB.pointsN[j]);
			if (foundSepAxis(axisB, boxA, boxB))
			{
				return false;
			}
			else
			{
				points[numOfAxis++] = axisB;
			}
		}

		minTransVec = getMinTransDist(points, numOfAxis);

		Point p(aPos.pointX - bPos.pointX, aPos.pointY - bPos.pointY);

		if (p.getDotProd(&minTransVec) < 0.0)
		{
			minTransVec.pointX *= -1;
			minTransVec.pointY *= -1;
		}

		return true;
	}
	return false;
}

bool Collision::isIntersect(BoundingQuad &boxA, 
	Point& aPos, 
	BoundingQuad &boxB, 
	Point& bPos, 
	Point& minTransVec)
{
	Point points[32];
	int numOfAxis = 0;
	for (unsigned int i = 0, j = boxA.getSize() - 1; i < boxA.getSize(); j = i, i++)
	{
		Point axisA = boxA.pointsN[i].getEdgeNormal(&boxA.pointsN[j]);
		if (foundSepAxis(axisA, boxA, boxB))
		{
			return false;
		}
		else
		{
			points[numOfAxis++] = axisA;
		}
	}

	for (unsigned int i = 0, j = boxB.getSize() - 1; i < boxB.getSize(); j = i, i++)
	{
		Point axisB = boxB.pointsN[i].getEdgeNormal(&boxB.pointsN[j]);
		if (foundSepAxis(axisB, boxA, boxB))
		{
			return false;
		}
		else
		{
			points[numOfAxis++] = axisB;
		}
	}

	minTransVec = getMinTransDist(points, numOfAxis);

	Point p(aPos.pointX - bPos.pointX, aPos.pointY - bPos.pointY);

	if (p.getDotProd(&minTransVec) < 0.0)
	{
		minTransVec.pointX *= -1;
		minTransVec.pointY *= -1;
	}

	return true;
}

Point Collision::getMinTransDist(Point* pushVectors, int numOfVectors)
{
	Point minTransVec = pushVectors[0];
	double sqlLength = pushVectors[0].getDotProd(&pushVectors[0]);

	for (unsigned int i = 0; i < numOfVectors; i++)
	{
		double sqlLengthI = pushVectors[i].getDotProd(&pushVectors[i]);

		if (sqlLengthI < sqlLength)
		{
			sqlLength = sqlLengthI;
			minTransVec = pushVectors[i];
		}
	}
	return minTransVec;
}