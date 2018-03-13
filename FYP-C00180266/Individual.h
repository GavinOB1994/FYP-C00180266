#pragma once
class Individual
{
public:

	//weightings
	int velX;
	int velY;

	int distanceFromGoal;
	
	//

	Individual();
	Individual(int x, int y);
	~Individual();

	void setFinalDist(int x);
};

