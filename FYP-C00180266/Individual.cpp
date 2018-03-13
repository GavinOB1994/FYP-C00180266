#include "stdafx.h"
#include "Individual.h"


Individual::Individual()
{
	velX = rand() % 60;
	velY = -(rand() % 60);
}


Individual::~Individual()
{
}

void Individual::setFinalDist(int x)
{
	distanceFromGoal = x;
}
