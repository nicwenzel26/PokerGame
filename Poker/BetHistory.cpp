//
// Created by Nic on 4/3/20.
//

#include "BetHistory.h"

//Clears the history of the bets
void BetHistory::clearHistory() {
    betHistory.clear();
}

//Adds a bet to the bet history
void BetHistory::addBet(Bet bet) {
    betHistory.push_back(bet);
}

//Get the number of bets in the bet history
int BetHistory::getCount() {
    return betHistory.size();
}

//Return the nth bet
Bet BetHistory::getBet(int n) {
    return betHistory[n];
}