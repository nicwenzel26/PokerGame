//
// Created by Nic on 4/3/20.
//

#ifndef POKER_HUMANPLAYER_H
#define POKER_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer: public Player {
public:
    HumanPlayer();

    HumanPlayer(int id1, int chips1);
};


#endif //POKER_HUMANPLAYER_H
