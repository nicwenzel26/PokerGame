//
// Created by Nic on 4/3/20.
//

#include "Bet.h"

Bet::Bet(int amount, int player) {
    this-> betAmount = amount;
    this-> playerWhoBet = player;
}

//Returns the amount of the bet
int Bet::getAmount() {
    return betAmount;
}

//Returns the player who bet
int Bet::getPlayer() {
    return playerWhoBet;
}
