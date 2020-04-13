//
// Created by Nic on 4/3/20.
//

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include "PlayerType.h"
#include "Player.h"
#include "AlphaPlayer.h"
#include "HumanPlayer.h"
#include "Deck.h"

class Game {
public:

    bool playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag);

private:
    int pot = 0;

    static void printVisable(Player *p1, Player *p2);
    static void dealInitHand(Player *p1, Player *p2,Deck &deck);
    void player1First(Player *p1, Player *p2, int &pot, int &p1Bet, int &p2Bet, BetHistory &bh);

};


#endif //POKER_GAME_H
