//
// Created by Nic on 4/4/20.
//

#ifndef POKER_DECK_H
#define POKER_DECK_H

#include "Card.h"
#include "Player.h"
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

class Deck {
public:
    //Constructor of deck
    Deck();

    //Clears the current deck
    void clearDeck();

    //Reset the deck to original 52
    void resetDeck();

    //Makes the deck
    void makeDeck();

    //Deals card to the player
    Card dealCard(bool faceUp);

    //Deal starting hand
    void dealStarting(Player &p1, Player &p2);

private:
    vector<Card> deck;

};


#endif //POKER_DECK_H
