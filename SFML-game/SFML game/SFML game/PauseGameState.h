#pragma once
#include "States.h"
#include "MainMenu.h"

class PauseGameState :public States
{
private:
	sf::Font font;
	sf::Text text;
	sf::Text winorlosetext;
	void initfont();
	void initBackground();
	void DisplayScore();
public:
	PauseGameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~PauseGameState() {};

	void setEvent(sf::Event& event);
	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imgui();
};


