#include "Ball.h"

void Ball::initSprite()
{
	this->sprite.setTexture(this->texture);
	sprite.scale(0.02f, 0.02f);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}
void Ball::initTexture()
{
	if (!this->texture.loadFromFile("Textures/ball.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BALL\n";
}

Ball::Ball(sf::VideoMode videoMode, sf::Vector2i newPos)
{
	initTexture();
	initSprite();
	this->sprite.setPosition(newPos.x, newPos.y);
	this->speed = videoMode.width/100;
}

Ball::~Ball()
{
}

void Ball::setPosition(int x, int y)
{
	this->sprite.setPosition(x,y);
}

void Ball::directions(int x, int y)
{
	sf::Vector2f ballpos = this->sprite.getPosition();
	float angle = std::atan2f(-(ballpos.y - y), -(ballpos.x - x));
	direction.x = std::cos(angle);
	direction.y = std::sin(angle);

}

void Ball::updateDirection( bool& changeX, bool& changeY)
{
	if (changeX == true)
		direction.x = -direction.x;
	if (changeY == true)
		direction.y = -direction.y;
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Ball::update(const float& dt)
{

	this->sprite.move(direction.x * this->speed*dt, direction.y * this->speed*dt);

}




