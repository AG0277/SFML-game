#pragma once
#include "States.h"
#include "MainMenu.h"
#include "LeaderboardState.h"

class PauseGameState :public States
{
private:
	sf::Font font;
	sf::Text text;
	sf::Text winorlosetext;
	std::string playerInput;
	sf::Text playerText;
	sf::Text playerDecision;
	unsigned int playerInputSize;
	bool YesNoInput;
	void initfont();
	void initBackground();
	void DisplayScore();
public:
	PauseGameState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~PauseGameState() {};

	void setEvent(sf::Event& event);
	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imguiGameON(); // show gui when game is on ( player didnt lose or win, keeps playing)
	void imguiGameOFF();
};


