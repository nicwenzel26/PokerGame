//
// Created by Nic on 4/3/20.
//

#ifndef POKER_BETHISTORY_H
#define POKER_BETHISTORY_H

#include "Bet.h"
#include <vector>

using namespace std;

class BetHistory {
public:
    //Clears the bet history
    void clearHistory();

    //Add a bet to the bet history
    void addBet(Bet bet);

    //Get the number of bets in the history
    int getCount();

    //Gets the nth bet in the history
    Bet getBet(int n);


private:
    vector<Bet> betHistory;

};


#endif //POKER_BETHISTORY_H
