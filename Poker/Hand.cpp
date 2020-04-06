//
// Created by Nic on 4/3/20.
//

#include "Hand.h"

//Clears the current hand
void Hand::clear() {
    hand.clear();
}

//Adds a card to current hand
void Hand::addCard(const Card& c) {
    hand.push_back(c);
}

//Get the number of cards in the hand
int Hand::getCount() {
    return hand.size();
}

//Return the nth card in the hand
Card Hand::getCard(int n) {
    return hand[n];
}

//Returns a hand of visible cards
Hand Hand::getVisible() {
    Hand visHand;
    for(auto c: hand) {
        if(c.isFaceUp()) {
            visHand.hand.push_back(c);
        }
    }

    return visHand;
}

//Evaluate the value of the hand.
int Hand::evaluate() {
    int val = 0;
    for(auto card: hand) {
        if(card.getValue() <= 10) {
            val += card.getValue();
        }
        else {
            val += 10;
        }
    }
    return val;
}
