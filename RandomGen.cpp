#include "RandomGen.h"
#include <random>

double RandomGen::getRand(double upper, double lower)
{
	this->upper = upper;
	this->lower = lower;

	double temp = (double)rand() / RAND_MAX;
	return lower + temp * (upper - lower);
}
