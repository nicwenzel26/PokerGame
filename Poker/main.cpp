#include <iostream>

#include "Game.h"
#include "PlayerType.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"

using namespace std;

int main() {
    Game game;
    bool done;
    done = game.playGame(ALPHA, ALPHA, 1000, 1000, true);

    if(done) {
        cout << "Game Ended.\n";
    }
    return 0;
}
