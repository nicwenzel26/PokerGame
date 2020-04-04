//
// Created by Nic on 4/3/20.
//

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include "PlayerType.h"

class Game {
public:

    bool playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag);

private:
    int pot = 0;

};


#endif //POKER_GAME_H
