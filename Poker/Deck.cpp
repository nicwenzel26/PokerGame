//
// Created by Nic on 4/4/20.
//

#include "Deck.h"

Deck::Deck(){
    makeDeck();
}


void Deck::clearDeck() {
    deck.clear();
}

void Deck::makeDeck() {
    vector<string> suites = {"Hearts", "Diamonds", "Clubs", "Spades"};

    for(auto suite: suites) {
        for(int i = 1; i <= 13; i++) {
            Card c = Card(suite, i);
            deck.push_back(c);
        }
    }
}

void Deck::resetDeck() {
    clearDeck();
    makeDeck();
}


Card Deck::dealCard(bool faceUp) {
    srand(time(nullptr));
    int pos = rand() % deck.size();
    Card c = deck[pos];
    deck.erase(deck.begin() + pos );
    c.setFaceUp(faceUp);
    return c;
}


