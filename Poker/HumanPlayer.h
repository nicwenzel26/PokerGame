//
// Created by Nic on 4/3/20.
//

#ifndef POKER_HUMANPLAYER_H
#define POKER_HUMANPLAYER_H

#include "Player.h"
#include <iostream>

using namespace std;

class HumanPlayer: public Player {
public:
    HumanPlayer();

    HumanPlayer(int id1, int chips1);

    int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) override;

private:
    void printHand();
};


#endif //POKER_HUMANPLAYER_H
