//
// Created by Nic on 4/3/20.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int id1, int chips1) : Player(id1, chips1) {

}

int HumanPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) {
    cout << "Your Bet:\n";
    //Print the full hand of the player
    printHand();

    //Print the bet history of the game
    cout << "\nBet History:\n";
    int betHistorySize = bh.getCount();
    for(int i = 1; i < betHistorySize; i++) {
        Bet b = bh.getBet(i);
        if(b.getAmount() != -1) {
            cout << b.getPlayer() << ": " << b.getAmount() << "\n";
        }
        else {
            cout << "\n";
        }
    }

    //Print the current pot of the game
    cout << "Current Pot: " << pot << "\n";
    int bet;

    //Prompt the user for a bet amount
    cout << "Enter bet: (0 for Call/Fold, 1-10 Raise, -1 Quit) ";
    cin >> bet;

    //Make sure the bet is valid
    while(bet > 10 || bet < -2) {
        cout << "Enter a valid bet (0 for Call/Fold, 1-10, -1 Quit) ";
        cin >> bet;
    }

    return bet;

}

//Method for printing the entire player hand, including face down cards
void HumanPlayer::printHand() {
    Hand hand  = this->getHand();
    int handSize = hand.getCount();

    cout << "Your Hand: \n";
    for(int i = 0; i < handSize; i++){
        Card c = hand.getCard(i);
        int val = c.getValue();
        if(val <= 10 && val > 1 ) {
            cout << val << " of ";
        } else {
            switch(val) {
                case 1: cout << "Ace of "; break;
                case 11: cout << "Jack of "; break;
                case 12: cout << "Queen of "; break;
                case 13: cout << "King of "; break;
            }
        }

        cout << c.getName() << ", ";
    }
}