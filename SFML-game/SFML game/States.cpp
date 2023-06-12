#include "pch.h"
#include "States.h"

int States::points = 0;
bool States::DidYouWin = false;
bool States::gameON = false;
float States::gameLevel=1;


States::States(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states)
{
	this->states = states;
	this->window = window;
	this->videoMode = videoMode;
	this->quitState = false;
	this->gui = new GUI(window);
}

States::~States()
{
	delete gui;
}

bool States::getQuit() 
{
	return this->quitState;
}

void States::writeScore(int score, const std::string& name)
{
	std::ofstream scoreFile("Score.txt", std::ios::app);
	if (scoreFile.is_open())
	{
		scoreFile << name << "->" << score << "\n";
		scoreFile.close();
	}
}
