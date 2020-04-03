//
// Created by Nic on 4/3/20.
//

#include "Card.h"

//Constructor for card
Card::Card(string cardName, int cardValue) {
    this->name = cardName;
    this->value = cardValue;
}

//Set the cards value
void Card::setCard(string cardName, int cardValue) {
    this->name = cardName;
    this->value = cardValue;
}

//Return the card name
string Card::getName() {
    return name;
}

//Return the value of the card
int Card::getValue() {
    return value;
}

//Return if the card is face up
bool Card::isFaceUp() {
    return faceUp;
}

//sets the face up status of the card. 
void Card::setFaceUp(bool face) {
    faceUp = face;
}

