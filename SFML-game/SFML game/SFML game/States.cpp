#include "States.h"

States::States(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states)
{
	this->states = states;
	this->window = window;
	this->videoMode = videoMode;
	this->quitState = false;
	this->gui = new GUI(this->window);
}

States::~States()
{

}

bool States::getQuit() 
{
	return this->quitState;
}
