#pragma once
#include<vector>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"
#include "Block.h"
#include "CollisionManager.h"
#include <map>
#include "GUI.h"
#include <stdlib.h>

class States
{
private:

protected:
	std::stack<States*>* states;
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	CollisionManager collision;
	bool quitState;
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackgroud;
	GUI* gui;

public:
	States(sf::RenderWindow* window, sf::VideoMode videoMode, std::stack<States*>* states);
	virtual ~States();

	virtual void setEvent(sf::Event& event) {};
	bool getQuit();
	void endState() { this->quitState = true; };
	virtual	void update(const float& deltaTime, sf::Time& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};


