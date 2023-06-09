#include "Block.h"



int BlockBall::counter = 0;
int BlockYellow::counter = 0;

void Block::updateHit()
{
	this->health -= 1;
	setColor();
}

void Block::initTexture()
{
	if (!this->texture.loadFromFile("Textures/Grey200.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	this->sprite.setTexture(this->texture);
	sprite.scale(0.4f, 0.4f);
}


std::vector<float> Block::getSpritePosition()
{

	std::vector<float> spritePos;
	float wallPosX = this->sprite.getGlobalBounds().left;
	float wallPosY = this->sprite.getGlobalBounds().top;
	float wallWidth = this->sprite.getGlobalBounds().width;
	float wallHeight = this->sprite.getGlobalBounds().height;
	spritePos.push_back(wallPosX);
	spritePos.push_back(wallPosY);
	spritePos.push_back(wallWidth);
	spritePos.push_back(wallHeight);
	return spritePos;
}

bool Block::update()
{
	if (this->health <= 0)
		return false;
	else
		return true;

}

void Block::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Block::setColor() 
{
	if (this->health < 20)
		this->sprite.setColor(sf::Color(0, 250, 0, 255));
	else if (this->health >= 20 && this->health < 40)
		this->sprite.setColor(sf::Color(250, 0, 0, 255));
	else if (this->health >= 40 && this->health < 60)
		this->sprite.setColor(sf::Color(250, 255, 16, 255));
	else if (this->health >= 60 && this->health < 80)
		this->sprite.setColor(sf::Color(100, 250, 0, 255));
	else if (this->health >= 80 && this->health < 90)
		this->sprite.setColor(sf::Color(73, 255, 213, 255));
	else if (this->health >= 90 && this->health < 100)
		this->sprite.setColor(sf::Color(255, 73, 250, 255));
	else if (this->health >= 100 && this->health < 110)
		this->sprite.setColor(sf::Color(73, 121, 255, 255));
	else if (this->health >= 110 && this->health < 120)
		this->sprite.setColor(sf::Color(140, 73, 213, 255));
	else if (this->health >= 120 && this->health < 130)
		this->sprite.setColor(sf::Color(201, 73, 255, 255));
}

int Block::getPoints()
{
	return this->points;
}


BlockYellow::BlockYellow(int health)
	:Block()
{
	initTexture();
	pair.first = 0;
	pair.second = 100;
	pair = std::make_pair(pair.first + this->sprite.getGlobalBounds().width * counter, pair.second );
	counter++;
	this->health = health;
	this->points = health;
	setColor();
}

BlockBall::BlockBall()
	:Block()
{
	counter++;
	pair.first = 200;
	pair.second = 350;
	pair = std::make_pair(pair.first *counter, pair.second *counter);
	initTexture();
	this->sprite.setPosition(pair.first, pair.second);
	this->health = 1;
	this->points = 2;
}

void BlockBall::initTexture()
{
	if (!this->texture.loadFromFile("Textures/ball2.png"))
		std::cout << "ERROR::FAILED TO LOAD TEXTURE BLOCK\n";
	this->sprite.setTexture(this->texture);
	sprite.scale(0.38f, 0.38f);
}