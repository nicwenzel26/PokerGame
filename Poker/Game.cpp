//
// Created by Nic on 4/3/20.
//

#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"
#include "Deck.h"
#include <iostream>

using namespace std;


bool Game::playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag) {
    //TODO ADD GAME FUNCTIONALITY
    Player*player1;
    Player* player2;

    //Setting fake data before set
    HumanPlayer human = HumanPlayer(-1, -1);
    AlphaPlayer alpha = AlphaPlayer(-1, -1);
    Deck deck = Deck();
    BetHistory bh = BetHistory();
    //Initial Empty bet.
    bh.addBet(Bet(-1, -1));

    //Set current round to 1
    int numRounds = 1;
    //Setting the quit condition
    bool quit = reportFlag;

    if(p0 == HUMAN) {
        human = HumanPlayer(0, chips0);
        alpha = AlphaPlayer(1, chips1);

        player1 = &human;
        player2 = &alpha;
    }
    else{
        alpha = AlphaPlayer(0, chips0);
        human = HumanPlayer(1, chips1);
        player1 = &alpha;
        player2 = &human;
    }

    while(numRounds <= 20 && !quit) {
        //Start of Round
        cout << "Round: " << numRounds << "\n";
        //Add chips from each player.
        player1->addChips(-10);
        player2->addChips(-10);
        int p1bet = 0;
        int p2bet = 0;

        //Add chips from each player to the pot;
        pot += 20;

        deck.resetDeck();

        player1->dealCard(deck.dealCard(true));
        player1->dealCard(deck.dealCard(true));
        player1->dealCard(deck.dealCard(false));

        player2->dealCard(deck.dealCard(true));
        player2->dealCard(deck.dealCard(true));
        player2->dealCard(deck.dealCard(false));


        printVisable(player1, player2);

        int betP1;
        int betP2;
        int lastBet = bh.getBet(bh.getCount() - 1).getAmount();
        if (numRounds % 2 != 0) {
            betP1 = player1->getBet(player2->getHand(), bh, lastBet, player1->getChips() >= 10, pot);

            //If the
            if (betP1 == -1) {
                quit = true;
            }
        }
        numRounds += 1;

    }

    return false;
}


void Game::printVisable(Player *p1, Player *p2) {
    Hand p1Vis = p1->getHand().getVisible();
    Hand p2Vis = p2->getHand().getVisible();

    int p1VisSize = p1Vis.getCount();
    int p2VisSize = p2Vis.getCount();

    cout << "Cards on the table: \n";
    cout << "Player 1: \n";
    for(int i = 0; i < p1VisSize; i++) {
        Card c = p1Vis.getCard(i);
        switch(c.getValue()) {
            case 1: cout << "Ace of "; break;
            case 2: cout << "2 of "; break;
            case 3: cout << "3 of "; break;
            case 4: cout << "4 of "; break;
            case 5: cout << "5 of "; break;
            case 6: cout << "6 of "; break;
            case 7: cout << "7 of "; break;
            case 8: cout << "8 of "; break;
            case 9: cout << "9 of "; break;
            case 10: cout << "10 of "; break;
            case 11: cout << "Jack of "; break;
            case 12: cout << "Queen of "; break;
            case 13: cout << "King of "; break;
        }
        cout << c.getName() << "\n";
    }

    cout << "Chips: " << p1->getChips() << "\n \n";

    cout << "Player 2: \n";
    for(int i = 0; i < p2VisSize; i++) {
        Card c = p2Vis.getCard(i);
        switch(c.getValue()) {
            case 1: cout << "Ace of "; break;
            case 2: cout << "2 of "; break;
            case 3: cout << "3 of "; break;
            case 4: cout << "4 of "; break;
            case 5: cout << "5 of "; break;
            case 6: cout << "6 of "; break;
            case 7: cout << "7 of "; break;
            case 8: cout << "8 of "; break;
            case 9: cout << "9 of "; break;
            case 10: cout << "10 of "; break;
            case 11: cout << "Jack of "; break;
            case 12: cout << "Queen of "; break;
            case 13: cout << "King of "; break;
        }
        cout << c.getName() << "\n";
    }

    cout << "Chips: " << p2->getChips() << "\n \n";
}