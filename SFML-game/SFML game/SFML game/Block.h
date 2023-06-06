#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CollisionManager.h"

class Block
{
protected:

	sf::Sprite sprite;
	sf::Texture texture;
	std::pair<int, int> pair;

	int health;
	int points;

	virtual void initSprite();
	virtual void initTexture();
public:
	Block() { setColor(); };
	virtual ~Block() { };
	virtual void setHealth(int health) { this->health = health; };
	virtual std::vector<float> getSpritePosition();
	virtual bool update();
	virtual void updateHit();
	virtual void render(sf::RenderTarget* target);
	virtual sf::Sprite* getSprite() { return &(this->sprite); };
	virtual int getHealth() { return this->health; };
	virtual void setColor();
	virtual int getPoints();

};



class BlockYellow :public Block
{
private:
	static int counter;
public:
	BlockYellow();
	~BlockYellow() { counter--; };

};


class BlockBlue :public Block
{
private:
	static int counter;
public:
	BlockBlue();
	~BlockBlue() { counter--; };

};


