//
// Created by Nic on 4/3/20.
//

#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"
#include <iostream>

using namespace std;

bool Game::playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag) {
    //TODO ADD GAME FUNCTIONALITY
    Player player1 = Player(0, chips0);
    Player player2 = Player(1, chips1);

    if(p0 == HUMAN) {
        player1 = HumanPlayer(0, chips0);
        player2 = AlphaPlayer(1, chips1);
    }



    return false;
}