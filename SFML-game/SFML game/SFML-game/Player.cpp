#include "Player.h"
// private functions

void Player::initSprite()
{
	texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
	sprite.scale(0.3f, 0.3f);
	sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/paddle.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE FILE";

}


// contructor, destructor 
Player::Player(sf::VideoMode videoMode)
{
	initTexture();
	initSprite();
	this->movmentSpeed = 1;
	this->startPosition(videoMode.width / 2 - videoMode.width * 0.05, videoMode.height * 0.75);

}

Player::~Player()
{

}


// functions

void Player::startPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::move(const float x, const float y)
{
	this->sprite.move(x * this->movmentSpeed, y * this->movmentSpeed);
}

void Player::update()
{

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}