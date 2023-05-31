#pragma once
#include <SFML/Graphics.hpp>

class RayTracing
{
private:
	sf::Window* window;
	sf::Vector2i mousePos;
	sf::Vector2i ballpos;
	sf::Texture texture;
	sf::Sprite sprite;
	bool turnON;
	sf::Vector2i lineSize; // deafult texture is 50,200
	sf::Vector2i linePos; // line starting position, top left corner
	void initSprite();
public:
	RayTracing();
	~RayTracing() {};

	void setTurnOn(bool turnON) { this->turnON = turnON; };
	bool getTurnOn() { return this->turnON; };
	void direction(sf::Vector2i mousePos, sf::Vector2i BallPos);
	void update(sf::Vector2i mousePos, sf::Vector2i BallPos);
	void render(sf::RenderTarget* target);
};

