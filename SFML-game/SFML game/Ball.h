#pragma once

class Ball
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	sf::Vector2f direction;

	int dt;
	int frameHitRefresh;
	bool hasBeenHit;

	void initSprite();
	void intervalBetweenCollisions();
public:
	Ball(const sf::VideoMode& videoMode, const sf::Vector2i& newPos,const sf::Texture& texture);
	~Ball();

	void sethasBeenHit(const bool& hasBeenHit) { this->hasBeenHit = hasBeenHit; };
	bool gethasBeenHit() { return this->hasBeenHit; }
	sf::Vector2f getDirections() { return this->direction; };
	sf::Sprite getSprite() { return this->sprite; };
	void setPosition(int x, int y);
	void directions(int x, int y);
	void updateDirection( bool& changeX, bool& changeY);
	void render(sf::RenderTarget* target);
	void update(const float& dt);

};

