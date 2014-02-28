#pragma once
#include "BoundingQuad.h"

class MyTranslate
{
private:
	double matrixArray[9];
public:
	MyTranslate();
	~MyTranslate();
	void makeIdentity(double* inputMatrix);
	void translate(double xTrans, double yTrans, BoundingQuad* box);
	void rotate(double angle, BoundingQuad* box);

	void multiplyTwoMatrix(double* matrixOne, double* matrixTwo, double* answerMatrix);

	void multiplyMatrixPostVector(double* matrix, double* xyhVector, double* answerVector);

	void multiplyMatrixPreVector(double* matrix, double* xyhVector, double* answerVector);

	void makeTranslateMatrix(double xTrans, double yTrans, double* tMatrix);

	void makeRotateMatrix(double angle, double* rMatrix);

	void makeXYHVector(double x, double y, double* xyzVector);
};

