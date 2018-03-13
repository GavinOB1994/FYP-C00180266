#include "stdafx.h"
#include "Individual.h"


Individual::Individual()
{
	velX = rand() % 60;
	velY = -(rand() % 60);
}

Individual::Individual(int x, int y)
{
	velX = x;
	velY = y;
}

Individual::~Individual()
{
}

void Individual::setFinalDist(int x)
{
	distanceFromGoal = x;
}
