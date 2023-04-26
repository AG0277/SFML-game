#include "Ball.h"

void Ball::initSprite()
{
	this->sprite.setTexture(this->texture);
	sprite.scale(0.03f, 0.03f);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}
void Ball::initTexture()
{
	if (!this->texture.loadFromFile("Textures/ball.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BALL\n";
}

Ball::Ball(sf::VideoMode videoMode)
{
	initTexture();
	initSprite();
	this->sprite.setPosition(videoMode.width / 2 - videoMode.width * 0.05, videoMode.height * 0.75);
	this->speed = 300;
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

void Ball::update(float& dt)
{

	this->sprite.move(direction.x * this->speed*dt, direction.y * this->speed*dt);

}




