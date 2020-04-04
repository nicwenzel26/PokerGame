//
// Created by Nic on 4/3/20.
//

#ifndef POKER_HAND_H
#define POKER_HAND_H

#include "Card.h"
#include <vector>

using namespace std;


class Hand {
public:
    //Clears the current hand of cards
    void clear();

    //Adds card to the hand
    void addCard(const Card& c);

    //Return how many cards are in the hand
    int getCount();

    //Returns the nth card in the hand
    Card getCard(int n);

    //Returns a hand of the cards that are visible
    Hand getVisible();

    //What is the value of the hand
    int evaluate();


private:
    vector<Card> hand;


};


#endif //POKER_HAND_H
