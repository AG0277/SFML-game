#pragma once


class Block
{
protected:

	sf::Sprite sprite;
	sf::Texture texture;
	std::pair<int, int> pair;

	int health;
	int points;

	virtual void initTexture();
public:
	Block() {};
	virtual ~Block() { };
	virtual void setHealth(int health) { this->health = health; };
	virtual std::vector<float> getSpritePosition();
	virtual bool update();
	virtual void updateHit();
	virtual void render(sf::RenderTarget* target);
	virtual sf::Sprite* getSprite() { return &(this->sprite); };
	virtual void setColor();
	virtual int getPoints();
};

class BlockYellow :public Block
{
private:
	static int counter;
public:
	BlockYellow(int health=90);
	~BlockYellow() { counter--; };
	 int getHealth() { return this->health; };
};


class BlockBall :public Block
{
private:
	static int counter;

	void initTexture();
public:
	BlockBall();
	~BlockBall() { counter--; };
};


