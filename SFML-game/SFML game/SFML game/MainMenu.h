#pragma once
#include"States.h"
#include"GameState.h"

class MainMenu:public States
{
private:

	void initBackground();
public:
	MainMenu(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~MainMenu() {};

	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imgui();
};


