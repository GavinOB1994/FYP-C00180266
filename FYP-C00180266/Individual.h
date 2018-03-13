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
	~Individual();

	void setFinalDist(int x);
};

