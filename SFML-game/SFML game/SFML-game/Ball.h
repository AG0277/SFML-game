#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "CollisionManager.h"

class Ball
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	sf::Vector2f direction;

	void initSprite();
	void initTexture();
public:
	Ball(sf::VideoMode videoMode, sf::Vector2i newPos);
	~Ball();

	sf::Sprite getSprite() { return this->sprite; };
	void setPosition(int x, int y);
	void directions(int x, int y);
	void updateDirection( bool& changeX, bool& changeY);
	void render(sf::RenderTarget* target);
	void update(const float& dt);

};

