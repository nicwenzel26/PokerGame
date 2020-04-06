//
// Created by Nic on 4/3/20.
//

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include "Hand.h"
#include "BetHistory.h"

//Parent player object
class Player {
public:
    //Constructor for the player
    Player(int id, int chips);

    //Get bet function
    virtual int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot ) = 0;

    //Return the id of the player
    int getID();

    //Clear hand
    void clearHand();

    //Deal a card to the hand
    void dealCard(Card c);

    //Get the players current hand
    Hand getHand();

    //Add chips to the players total
    void addChips(int chips);

    //Get the total chips the player has
    int getChips();


private:
    int id;
    int chips;
    Hand playerHand;


};


#endif //POKER_PLAYER_H
