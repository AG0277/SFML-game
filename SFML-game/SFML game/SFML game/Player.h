#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movmentSpeed;
	void initSprite();
	void initTexture();
public:
	Player(sf::VideoMode videoMode);
	~Player();

	void startPosition(float x, float y);
	void move(const float x, const float y);
	void update();
	void render(sf::RenderTarget* target);

};

