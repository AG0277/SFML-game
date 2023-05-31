#include "RayTracing.h"

void RayTracing::initSprite()
{
	this->texture.loadFromFile("Textures/line.png");
	this->sprite.setTexture(texture);
	//sprite.setScale(0.1, 0.1);
	turnON = false;
}

RayTracing::RayTracing()
{
	initSprite();
	//this->window = window;
}

void RayTracing::direction(sf::Vector2i mousePos, sf::Vector2i BallPos)
{
	this->mousePos = mousePos;
	this->ballpos = BallPos;
	linePos.x = this->ballpos.x;
	linePos.y = this->mousePos.y;
	// size
	float PI = 3.1415926535;
	lineSize = this->mousePos - this->ballpos;
	lineSize.y = std::abs(lineSize.y);
	sprite.setRotation(180 - std::acos((BallPos.x - mousePos.x) / (BallPos.y - mousePos.y)) * 180 / PI);
	sprite.setPosition(mousePos.x, mousePos.y);
}

void RayTracing::update(sf::Vector2i mousePos, sf::Vector2i BallPos)
{
	this->mousePos = mousePos;
	this->ballpos = BallPos;
	linePos.x = this->ballpos.x;
	linePos.y = this->mousePos.y;
	// size
	float PI = 3.1415926535;
	lineSize = this->mousePos - this->ballpos;
	lineSize.y = std::abs(lineSize.y);
	sprite.setRotation(180 - std::acos((BallPos.x - mousePos.x) / (BallPos.y - mousePos.y)) * 180 / PI);
	sprite.setPosition(linePos.x, linePos.y);
}

void RayTracing::render(sf::RenderTarget* target)
{
	if (turnON == true)
		target->draw(this->sprite);
}
