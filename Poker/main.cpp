#include <iostream>

#include "Game.h"
#include "PlayerType.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"

using namespace std;

int main() {
    Game game;
    HumanPlayer humanPlayer = HumanPlayer(0, 1000);
    AlphaPlayer alphaPlayer = AlphaPlayer(1, 1000);

    game.playGame(HUMAN, ALPHA, humanPlayer.getChips(), alphaPlayer.getChips(), false);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
