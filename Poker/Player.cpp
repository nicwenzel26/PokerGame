//
// Created by Nic on 4/3/20.
//

#include "Player.h"

//Constructor for the parent player object
Player::Player(int id, int chips){
    this->id = id;
    this->chips = chips;
}

//
int Player::getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) {
    return -1;
    //TODO IMPLEMENT THE GET BET FUNCTION
}

int Player::getID() {
    return id;
}

//Clear the current player hand
void Player::clearHand() {
    playerHand.clear();
}

//Deal a card into the current player hand
void Player::dealCard(Card c) {
    playerHand.addCard(c);
}

//Return the players current hand
Hand Player::getHand() {
    return playerHand;
}

//Add or subtract chips from the player
void Player::addChips(int chips) {
    this->chips += chips;
}

//Get the players number of chips
int Player::getChips() {
    return chips;
}


