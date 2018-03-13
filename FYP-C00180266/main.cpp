// FYP-C00180266.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Individual.h"
#include <vector>
#include "SFML\Graphics.hpp"
#include <Windows.h>
#include <string> 

void newGen(std::vector<std::vector<Individual>>* list, int gen) //in here we asses the fitness and create the new gen
{
	int memberOne = 0;
	int memberTwo = 0;
	int memberThree = 0;

	for (int i = 0; i < 10; i++)
	{
		if ((*list)[gen][i].distanceFromGoal < (*list)[gen][memberOne].distanceFromGoal)
		{
			memberThree = memberTwo;
			memberTwo = memberOne;
			memberOne = i;
		}
		else if ((*list)[gen][i].distanceFromGoal < (*list)[gen][memberTwo].distanceFromGoal)
		{
			memberThree = memberTwo;
			memberTwo = i;
		}
		else if ((*list)[gen][i].distanceFromGoal < (*list)[gen][memberThree].distanceFromGoal)
		{
			memberThree = i;
		}
		
	}

	std::vector<Individual> newGen;
	(*list).push_back(newGen);

	Individual One = (*list)[gen][memberOne];
	Individual Two = (*list)[gen][memberTwo];
	Individual Three = (*list)[gen][memberThree];

	/*0*/ (*list)[gen + 1].push_back((*list)[gen][memberOne]);
	/*1*/ (*list)[gen + 1].push_back((*list)[gen][memberTwo]);
	/*2*/ (*list)[gen + 1].push_back((*list)[gen][memberThree]);
	/*3*/ (*list)[gen + 1].push_back(Individual(One.velX, Two.velY));
	/*4*/ (*list)[gen + 1].push_back(Individual(Two.velX, One.velY));
	/*5*/ (*list)[gen + 1].push_back(Individual(One.velX, Three.velY));
	/*6*/ (*list)[gen + 1].push_back(Individual(Three.velX, One.velY));
	/*7*/ (*list)[gen + 1].push_back(Individual(Three.velX, Two.velY));
	/*8*/ (*list)[gen + 1].push_back(Individual(Two.velX, Three.velY));
	/*9*/ (*list)[gen + 1].push_back(Individual());


	//heres the code for breeding the new generation
}

int main()
{
	//seeding random
	srand(time(NULL));

	//generations
	std::vector<std::vector<Individual>> generations;
	std::vector<Individual> gen1;
	generations.push_back(gen1);

	int currIndividual = 0;
	int currGen = 0;
	for (int i = 0; i < 10; i++){
		generations[0].push_back(Individual());
	}

	//Renderer
	sf::RenderWindow window(sf::VideoMode(1200, 800), "0, 0");

	//physics ball

	sf::CircleShape shape(10.f);
	sf::Vector2f pos(0, 700);
	sf::Vector2f vel(generations[0][0].velX, generations[0][0].velY);
	sf::Vector2f grav(0, 1);
	shape.setFillColor(sf::Color::Blue);

	//Goal
	sf::RectangleShape goal(sf::Vector2f(10, 20));
	sf::Vector2f goalPos(1000, rand() % 780);
	goal.setPosition(goalPos);
	goal.setFillColor(sf::Color::Green);

	//borders
	sf::VertexArray floor(sf::LinesStrip, 2);
	floor[0].position = sf::Vector2f(0, 720);
	floor[1].position = sf::Vector2f(1010, 720);
	
	sf::VertexArray wall(sf::LinesStrip, 2);
	wall[0].position = sf::Vector2f(1010, 0);
	wall[1].position = sf::Vector2f(1010, 720);

	////Text
	//sf::String debugText;
	//debugText.SetFont
	

	//Time
	int currentTime = GetTickCount();
	int deltaTime = 0;
	int timeStarted = GetTickCount(); //time per individual

	while (window.isOpen())
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		//*code here*
		if ((int)pos.x > 1000 || GetTickCount() - timeStarted > 7000)
		{
			
			if (GetTickCount() - timeStarted > 7000)
			{
				generations[currGen][currIndividual].setFinalDist(2000); //sets the value to an impossibly large one if it doesnt reach the goal
			}
			else
			{
				generations[currGen][currIndividual].setFinalDist(abs(pos.y - goalPos.y)); //setting the distance ofr the member for the fitness function
			}
			
			if (currIndividual == 9)
			{
				newGen(&generations, currGen); //generates new generation
				currGen++;
				currIndividual = -1;
			}

			currIndividual++;

			//sets the physics object to have the properties of the new member
			pos = sf::Vector2f(0, 700);

			
			vel = sf::Vector2f(generations[currGen][currIndividual].velX, generations[currGen][currIndividual].velY); 



			//reset time since new member
			timeStarted = GetTickCount();
		}

		deltaTime = GetTickCount() - currentTime;

		if (deltaTime > 1000 / 60 )
		{
			currentTime = GetTickCount();

			vel += grav;
			pos += vel;
			if (pos.y > 700) //floor
			{
				pos.y = 700;
			}
			shape.setPosition(pos);

			//sets the title for debuging
			window.setTitle(std::to_string(currGen) + ", " + std::to_string(currIndividual) + " : " + std::to_string(GetTickCount() - timeStarted));
		}



		/////////////////////////////////////////////////////////////////////////////////////////////
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.draw(goal);
		window.draw(floor);
		window.draw(wall);
		window.display();
	}

	//we should be looping the genetic algorithm here 
	//generations should be stored like [Generation, Individual] in a 2D array
	//we iterate through a generation and asses fitness
	//the top 3(?) most fit individuals get passed on immediatley, then crossbreeds are made, then random selection
	//repeat untill global minimum is reached
    return 0;
}


