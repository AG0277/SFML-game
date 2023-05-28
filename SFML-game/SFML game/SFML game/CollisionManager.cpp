#include "CollisionManager.h"



bool CollisionManager::handleCollisions(Ball& ball, Block& block, bool& changeX, bool& changeY) {

    bool checkX = false;
    bool checkY = false;
    float radius = 0;
        //ball.getSprite().getGlobalBounds().width / 2;
    if(block.getSprite()->getGlobalBounds().intersects(ball.getSprite().getGlobalBounds()))
    { 
        if (check_collision(ball.getSprite(), *block.getSprite()))
        {
            if (ball.getSprite().getPosition().y + radius >= block.getSpritePosition().at(1) + block.getSpritePosition().at(3) || ball.getSprite().getPosition().y - radius <= block.getSpritePosition().at(1))
            {
                changeY = true;
                checkX = true;

            }
            if (ball.getSprite().getPosition().x + radius >= block.getSpritePosition().at(0) + block.getSpritePosition().at(2) || ball.getSprite().getPosition().x - radius <= block.getSpritePosition().at(0))
            {
                changeX = true;
                checkY = true;
            }
            if (checkY || checkX == true)
            {
                return true;
            }
        }
    }


    
    return false;
}

bool CollisionManager::handleBackground_BallCollisions(Ball& ball, sf::Sprite& worldbackground, bool& changeX, bool& changeY,bool& delBall,bool& newPos)
{
    bool checkX = false;
    bool checkY = false;
    float radius = ball.getSprite().getGlobalBounds().width / 2;
    if (ball.getSprite().getPosition().y - radius <= worldbackground.getGlobalBounds().top)
    {
        changeY = true;
        checkY = true;
        ball.setPosition(ball.getSprite().getPosition().x, worldbackground.getGlobalBounds().top+ radius *1.4);
    }
    else if(ball.getSprite().getPosition().y + radius >= worldbackground.getGlobalBounds().top + worldbackground.getGlobalBounds().height)
    {
        checkY = true;
        //ball.setPosition(ball.getSprite().getPosition().x, worldbackground.getGlobalBounds().top+worldbackground.getGlobalBounds().height- radius * 1.4);
        if (this->newPos == false)
        {
            newPos = true;
            this->newPos = true;
        }
        delBall = true;
    }


    if (ball.getSprite().getPosition().x + radius >= worldbackground.getGlobalBounds().left + worldbackground.getGlobalBounds().width )
    {
        changeX = true;
        checkX = true;
       ball.setPosition(worldbackground.getGlobalBounds().left + worldbackground.getGlobalBounds().width - radius*1.4, ball.getSprite().getPosition().y);
    }
    else if(ball.getSprite().getPosition().x - radius - 5 <= worldbackground.getGlobalBounds().left)
    {
        changeX = true;
        checkX = true;
        ball.setPosition(worldbackground.getGlobalBounds().left + radius * 1.4, ball.getSprite().getPosition().y);
    }
    if(checkY ||checkX ==true)
    {
        return true;
    }

    return false;
}

bool CollisionManager::handleBackground_BlockCollisions(Block& block, sf::Sprite& worldbackground)
{
    int k = block.getSprite()->getGlobalBounds().top;
    int h= block.getSprite()->getGlobalBounds().height;
    int y = worldbackground.getGlobalBounds().top + worldbackground.getGlobalBounds().height;
    if (block.getSprite()->getGlobalBounds().top + block.getSprite()->getGlobalBounds().height >= worldbackground.getGlobalBounds().top + worldbackground.getGlobalBounds().height)
    {
        return true;
    }
    return false;
}

float CollisionManager::dot_product(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
sf::Vector2f CollisionManager::perpendicular(const sf::Vector2f& v) {
    return sf::Vector2f(-v.y, v.x);
}
bool CollisionManager::check_collision(sf::Sprite ball, sf::Sprite square) {
    // Get the positions of the center of the ball and square
    sf::Vector2f ball_center = ball.getPosition();//+ sf::Vector2f(ball.getGlobalBounds().width / 2, ball.getGlobalBounds().height / 2);
    sf::Vector2f square_center = square.getPosition() + sf::Vector2f(square.getGlobalBounds().width / 2, square.getGlobalBounds().height / 2);

    // Get the half-width and half-height of the square
    float half_width = square.getGlobalBounds().width / 2;
    float half_height = square.getGlobalBounds().height / 2;
    float distance = std::sqrt(std::pow(ball_center.x - square_center.x, 2) + std::pow(ball_center.y - square_center.y, 2));
    //if (distance <= ball.getGlobalBounds().width / 2 + square.getGlobalBounds().width / 2 + 5.f) {
        // Get the vertices of the square
        sf::Vector2f temp (2.f, 2.f);
        sf::Vector2f vertices[4];
        vertices[0] = square.getPosition()+temp;
        vertices[1] = vertices[0] + sf::Vector2f(square.getGlobalBounds().width-4, 0);
        vertices[2] = vertices[0] + sf::Vector2f(0, square.getGlobalBounds().height-4);
        vertices[3] = vertices[0] + sf::Vector2f(square.getGlobalBounds().width-4, square.getGlobalBounds().height-4);

        // Create an array of axes to project the shapes onto
        std::vector<sf::Vector2f> axes(4);
        for (int i = 0; i < 4; i++) {
            sf::Vector2f edge = vertices[(i + 1) % 4] - vertices[i];
            sf::Vector2f axis(-edge.y, edge.x);
            axes[i] = axis / std::sqrt(axis.x * axis.x + axis.y * axis.y);
        }

        // Add the axis from the center of the square to the center of the ball
        sf::Vector2f axis = ball_center - square_center;
        axes.push_back(axis / std::sqrt(axis.x * axis.x + axis.y * axis.y));

        // Project both shapes onto each axis and check for overlap
        for (const auto& axis : axes) {
            // Project the ball onto the axis
            float ball_min = std::numeric_limits<float>::infinity();
            float ball_max = -std::numeric_limits<float>::infinity();
            float dot = dot_product(axis, ball_center);
            ball_min = dot - ball.getGlobalBounds().width / 2;
            ball_max = dot + ball.getGlobalBounds().width / 2;

            // Project the square onto the axis
            float square_min = std::numeric_limits<float>::infinity();
            float square_max = -std::numeric_limits<float>::infinity();
            for (const auto& vertex : vertices) {
                dot = dot_product(axis, vertex);
                if (dot < square_min) {
                    square_min = dot;
                }
                if (dot > square_max) {
                    square_max = dot;
                }
            }

            // Check for overlap on this axis
            if (ball_max < square_min || square_max < ball_min) {
                // The shapes don't overlap on this axis, so they don't collide
                return false;
            }
        }
    
    
    // The shapes overlap on all axes, so they collide
    return true;
}