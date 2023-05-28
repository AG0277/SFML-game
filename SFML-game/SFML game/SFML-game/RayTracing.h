#pragma once
#include <SFML/Graphics.hpp>

class RayTracing
{
private:
	sf::Window* window;
	sf::Vector2f directionpos;
	sf::Vector2i ballpos;
	sf::Texture texture;
	sf::Sprite sprite;

	void initSprite();
public:
	RayTracing();
	~RayTracing() {};

	void direction(sf::Vector2f& direction);
	void update();
	void render(sf::RenderTarget* target);
};

