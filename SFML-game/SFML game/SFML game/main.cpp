#include "Game.h"
#include <sstream>

int main()
{
    Game game;

    while (game.running())
    {
        game.updateDeltaTime();
        if (game.update())
            game.render();

    }
    return 0;
}