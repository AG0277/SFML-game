#include "Game.h"
#include <sstream>

void test2()
{
    Game game;

    while (game.running())
    {
        game.updateDeltaTime();
        if (game.update())
            game.render();

    }


}
void test()
{

    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::Texture block50;
    block50.loadFromFile("Textures/Grey200.png");
    sf::Sprite block51;
    block51.setTexture(block50);
    block51.setColor(sf::Color(250, 0, 0, 255));
    block51.setColor(sf::Color(0, 250, 0, 255));
    //shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(block51);
        window.display();
    }
}

void tst4()
{
    const char* character = "sdadadasdas";
}
int main()
{

    //tst4();
    //test();
    test2();
    return 0;
}