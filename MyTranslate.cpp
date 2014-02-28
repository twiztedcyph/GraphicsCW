#include "MyTranslate.h"
#include <iostream>
#include <math.h>

MyTranslate::MyTranslate()
{
}


MyTranslate::~MyTranslate()
{
}

void MyTranslate::makeIdentity(double* inputMatrix)
{
	//Set all values in the array to zero.
	for (int i = 0; i < sizeof(inputMatrix); i++)
	{
		inputMatrix[i] = 0;
	}
	// Set the first, fifth and ninth element to 1. This forms
	// the identity matrix.
	inputMatrix[0] = 1.0;
	inputMatrix[4] = 1.0;
	inputMatrix[8] = 1.0;
}

void MyTranslate::makeTranslateMatrix(double xTrans, double yTrans, double* tMatrix)
{
	makeIdentity(tMatrix);
	tMatrix[2] = xTrans;
	tMatrix[5] = yTrans;
}

void MyTranslate::makeRotateMatrix(double angle, double* rMatrix)
{
	makeIdentity(rMatrix);
	rMatrix[0] = cos(angle);
	rMatrix[1] = -sin(angle);
	rMatrix[3] = -rMatrix[1];
	rMatrix[4] = rMatrix[0];
}

void MyTranslate::makeXYHVector(double x, double y, double* xyhVector)
{
	xyhVector[0] = x;
	xyhVector[1] = y;
	xyhVector[2] = 1.0;
}

void MyTranslate::multiplyTwoMatrix(double* matrixOne, double* matrixTwo, double* answerMatrix)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		int iT = i * 3;
		for (unsigned int j = 0; j < 3; j++)
		{
			answerMatrix[iT + j] = (matrixOne[iT + 0] * matrixTwo[j]) + (matrixOne[iT + 1] * matrixTwo[j + 3]) 	+ (matrixOne[iT + 2] * matrixTwo[j + (2 * 3)]);
		}
	}
}

void MyTranslate::multiplyMatrixPostVector(double* matrixOne, double* xyhVector, double* answerVector)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		int iT = i * 3;
		answerVector[i] 
			= (matrixOne[iT] * xyhVector[0]) 
			+ (matrixOne[iT + 1] * xyhVector[1]) 
			+ (matrixOne[iT + 2] * xyhVector[2]);
	}
}

void MyTranslate::multiplyMatrixPreVector(double* matrixOne, double* xyhVector, double* answerVector)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		answerVector[i]
			= (matrixOne[i + 0] * xyhVector[0])
			+ (matrixOne[i + 3] * xyhVector[1])
			+ (matrixOne[1 + 6] * xyhVector[2]);
	}
}
