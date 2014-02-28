#include "Point.h"
#include <math.h>


Point::Point()
{
}

Point::Point(double pointX, double pointY)
{
	this->pointX = pointX;
	this->pointY = pointY;
}

Point::~Point()
{
}

/*
void setPoint(double pointX, double pointY);
double getPointX();
double getPointY();

*/

void Point::setPoint(double pointX, double pointY)
{
	this->pointX = pointX;
	this->pointY = pointY;
}

double Point::getPointX()
{
	return this->pointX;
}

double Point::getPointY()
{
	return this->pointY;
}

double Point::getMagnitude()
{
	return sqrt((pointX * pointX) + (pointY * pointY));
}

Point Point::getNorm()
{
	double mag = getMagnitude();
	Point result;
	result.pointX = this->pointX / mag;
	result.pointY = this->pointY / mag;
	return result;
}

double Point::getDotProd(const Point* otherPoint)
{
	return ((this->pointX * otherPoint->pointX) + (this->pointY * otherPoint->pointY));
}

Point Point::projectToPoint(const Point* otherPoint)
{
	Point result;
	double dotProd = getDotProd(otherPoint);

	result.pointX = (dotProd / (otherPoint->pointX * otherPoint->pointX + otherPoint->pointY * otherPoint->pointY)) * otherPoint->pointX;
	result.pointY = (dotProd / (otherPoint->pointX * otherPoint->pointX + otherPoint->pointY * otherPoint->pointY)) * otherPoint->pointY;

	return result;
}

Point Point::getEdgeNormal(Point* otherPoint)
{
	double xResult = otherPoint->pointX - this->pointX;
	double yResult = otherPoint->pointY - this->pointY;
	Point result(-yResult, xResult);
	return result;
}

Point Point::projectToLine(const Point* lineStart, const Point* lineEnd)
{
	Point result;
	
	double m = (lineEnd->pointY - lineStart->pointY) / (lineEnd->pointX - lineStart->pointX);
	double b = lineStart->pointY - (m * lineStart->pointX);

	double x = (m * this->pointY + this->pointX - m * b) / (m * m + 1);
	double y = (m * m * this->pointY + m * this->pointX + b) / (m * m + 1);
	result.setPoint(x, y);

	return result;
}