#include <iostream>

#include "Game.h"
#include "PlayerType.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"

using namespace std;

int main() {
    Game game;

    game.playGame(HUMAN, ALPHA, 1000, 1000, false);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
