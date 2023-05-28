#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Block.h"

class Block;
class Ball;
class CollisionManager {
    bool newPos;
public:
    CollisionManager() : newPos(false) {};
    void setnewPos() { this->newPos = false; };
    bool handleCollisions(Ball& ball, Block& block, bool& changeX, bool& changeY);
    bool handleBackground_BallCollisions(Ball& ball, sf::Sprite& worldbackground, bool& changeX, bool& changeY, bool& delBall, bool& newPos);
    bool handleBackground_BlockCollisions(Block& block, sf::Sprite& worldbackground);
    float dot_product(const sf::Vector2f& v1, const sf::Vector2f& v2);
    sf::Vector2f perpendicular(const sf::Vector2f& v);
    bool check_collision(sf::Sprite ball, sf::Sprite square);
}; 