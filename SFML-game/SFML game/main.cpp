#include "pch.h"

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