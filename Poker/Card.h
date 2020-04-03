//
// Created by Nic on 4/3/20.
//

#ifndef POKER_CARD_H
#define POKER_CARD_H

#include <string>
using namespace std;


class Card {

public:
    //Instructor for a card
    Card(string cardName, int cardValue);

    //Set the cards value
    void setCard(string cardName, int cardValue);

    //Get the cards name.
    string getName();

    //Get the value of the the card
    int getValue();

    //Get if the card is face up to all the other players
    bool isFaceUp();

    //Set if the card is face up to all the other players
    void setFaceUp(bool face);


private:
    string name;
    bool faceUp;
    int value;

};


#endif //POKER_CARD_H
