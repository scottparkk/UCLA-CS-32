#include "globals.h"
#include "Gark.h"
#include "Player.h"
#include "Mesa.h"
#include "Game.h"
#include "History.h"

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(4, 4, 3);

    // Play the game
    g.play();
}



