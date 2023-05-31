#pragma once
#include"States.h"
#include"GameState.h"

class MainMenu:public States
{
private:
	sf::Font font;
	sf::Text text;

	void initfont();
	void initBackground();
public:
	MainMenu(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~MainMenu() {};

	void gameTitle();
	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imgui();
};


