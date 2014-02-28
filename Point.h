#pragma once

class Point
{
private:
	
public:
	double pointX;
	double pointY;
	Point();
	~Point();

	Point(double pointX, double pointY);
	void setPoint(double pointX, double pointY);
	
	double getPointX();
	double getPointY();
	double getMagnitude();
	Point getNorm();
	Point getEdgeNormal(Point* otherPoint);
	double getDotProd(const Point* otherPoint);
	Point projectToPoint(const Point* otherPoint);
	Point projectToLine(const Point* lineStart, const Point* lineEnd);
};

