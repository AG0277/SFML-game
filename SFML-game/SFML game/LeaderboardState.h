#pragma once
#include "states.h"

class LeaderboardState:public States
{
private:
	sf::Font font;
	sf::Text text;
	sf::Text leaderboardtext;
	std::vector<std::pair<std::string, int>> displayOveralScore;

	void sort(std::vector<std::pair<std::string, int>>& score, int howmanynumbers);
	void readScore();
	void initfont();
	void initBackground();
	void leaderboardDisplay();

public:
	LeaderboardState(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~LeaderboardState() {};

	void setEvent(sf::Event& event);
	void update(const float& deltaTime, sf::Time& dt);
	void render(sf::RenderTarget* target);
	void imgui();


};

