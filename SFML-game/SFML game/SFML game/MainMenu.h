#pragma once
#include"States.h"
#include"GameState.h"
#include "LeaderboardState.h"

class MainMenu:public States
{
private:
	sf::Font font;
	sf::Text text;
	bool displayNewGame;
	void initfont();
	void initBackground();
	void gameTitle();
public:
	MainMenu(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~MainMenu() {};

	void selectDifficulty();
	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imgui();
};


