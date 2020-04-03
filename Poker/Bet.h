//
// Created by Nic on 4/3/20.
//

#ifndef POKER_BET_H
#define POKER_BET_H


class Bet {
public:
    //Constructor for the bet
    Bet(int amount, int player);

    //Returns the player
    int getPlayer();

    //Returns the amount of the bet
    int getAmount();



private:
    int betAmount;
    int playerWhoBet;

};


#endif //POKER_BET_H
