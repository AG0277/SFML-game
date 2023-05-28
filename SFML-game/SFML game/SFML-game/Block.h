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

	virtual void initSprite() = 0;
	virtual void initTexture() = 0;
public:
	Block() { setColor(); };
	virtual ~Block() { };
	virtual std::vector<float> getSpritePosition();
	virtual bool update();
	virtual void updateHit();
	virtual void render(sf::RenderTarget* target);
	virtual sf::Sprite* getSprite() { return &(this->sprite); };
	virtual int getHealth() { return this->health; };
	virtual void setColor();

};



class BlockYellow :public Block
{
private:
	void initTexture();
	void initSprite();
	static int counter;
public:
	BlockYellow();
	~BlockYellow() { counter--; };

};


class BlockBlue :public Block
{
private:
	void initTexture();
	void initSprite();
	static int counter;
public:
	BlockBlue();
	~BlockBlue() { counter--; };

};


