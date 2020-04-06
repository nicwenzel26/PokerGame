//
// Created by Nic on 4/3/20.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int id1, int chips1) : Player(id1, chips1) {

}

int HumanPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) {
    cout << "Human Bet:\n";
    printHand();
    cout << "Bet History:\n";
    int betHistorySize = bh.getCount();

    for(int i = 0; i < betHistorySize; i++) {
        Bet b = bh.getBet(i);
        cout << b.getPlayer() << ": " << b.getAmount() << "\n";
    }

    cout << "Current Pot: " << pot << "\n";
    int bet;

    cout << "Enter bet: (0 for Call/Fold, 1-10 Raise, -1 Quit) ";
    cin >> bet;

    return bet;

}

//Method for printing the entire player hand, including face down cards
void HumanPlayer::printHand() {
    Hand hand  = this->getHand();
    int handSize = hand.getCount();

    cout << "\nHuman Hand: \n";
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

        cout << c.getName() << "\n";
    }
}