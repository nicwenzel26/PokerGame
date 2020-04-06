//
// Created by Nic on 4/3/20.
//

#ifndef POKER_ALPHAPLAYER_H
#define POKER_ALPHAPLAYER_H

#include "Player.h"

class AlphaPlayer: public Player  {
public:
    AlphaPlayer(int id, int chips);
    AlphaPlayer();

    int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) override;

};



#endif //POKER_ALPHAPLAYER_H
