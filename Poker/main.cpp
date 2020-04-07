#include <iostream>

#include "Game.h"
#include "PlayerType.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"

using namespace std;

int main() {
    Game game;
    bool done;
    done = game.playGame(HUMAN, ALPHA, 1000, 1000, false);

    if(done) {
        cout << "Game Ended.\n";
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
