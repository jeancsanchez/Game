#include "Game.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game engine
    Game game;
    
    while (game.isRunning())
    {
        game.update();
        game.render();
    }

    return 0;
}