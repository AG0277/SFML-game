#include "RayTracing.h"

void RayTracing::initSprite()
{
	this->texture.loadFromFile("Textures/line.png");
	this->sprite.setTexture(texture);
}

RayTracing::RayTracing()
{
	//this->window = window;
}

void RayTracing::direction(sf::Vector2f& direction)
{
	this->directionpos = direction;
	this->ballpos = sf::Vector2(500, 500);
}

void RayTracing::update()
{

}

void RayTracing::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
