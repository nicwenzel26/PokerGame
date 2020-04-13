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
    bh = BetHistory();
    //Initial Empty bet.
    bh.addBet(Bet(0, -1));

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

    //While there are still round to play and while the player doesn't want to quit.
    while(numRounds <= 20 && !quit) {
        //Start of Round
        cout << "Round: " << numRounds << "\n";
        //Add chips from each player.
        player1->addChips(-10);
        player2->addChips(-10);

        //Set initial bet to 0 for both players
        int p1bet = 0;
        int p2bet = 0;

        //Add chips from each player to the pot;
        pot += 20;

        //Reset the decks cards
        deck.resetDeck();

        //Deal the initial hand of the round
        dealInitHand(player1, player2, deck);

        //Printing the visible hands of bother of the players
        printVisable(player1, player2);


        //Alternate who starts the betting rounds
        if(numRounds % 2 != 0) {
            quit = playHand(player1, player2, deck, pot);
        }
        else {
            quit  = playHand(player2, player1, deck, pot);
        }



        //At the end of the round clear the players hands
        player1->clearHand();
        player2->clearHand();

        //Clearing the bet history
        bh.clearHistory();

        //Resetting the pot
        pot = 0;

        //Increment the number of rounds
        numRounds += 1;

    }

    //Handling the winning condition
    if(player1->getChips() > player2->getChips()) {
        cout << "Player 1 Wins!!\n";
    }
    else {
        cout << "Player 2 Wins!!\n";
    }

    return true;
}


bool Game::playHand(Player *p1, Player *p2, Deck &deck, int &pot) {
    int status;
    //First betting round
    status  = betRound(p1, p2);
    //Both players are still in the game
    if(status == -1) {
        p1->dealCard(deck.dealCard(true));
        p2->dealCard(deck.dealCard(true));
        printVisable(p1, p2);
        status = betRound(p1, p2);
        //Both players are still in the game
        //Deal Second Card
        if(status == -1) {
            p1->dealCard(deck.dealCard(true));
            p2->dealCard(deck.dealCard(true));
            printVisable(p1, p2);
            status = betRound(p1, p2);
            //Both players are still in the game
            //Final betting Round
            if(status == -1) {
                p1->dealCard(deck.dealCard(true));
                p2->dealCard(deck.dealCard(true));
                printVisable(p1, p2);
                status = betRound(p1, p2);
                //Both players are still in the game
                if(status == -1){
                    //Flipping the hidden cards
                    p1->getHand().getCard(0).setFaceUp(true);
                    p2->getHand().getCard(0).setFaceUp(true);
                    printVisable(p1, p2);
                    int p1Worth = p1->getHand().evaluate();
                    int p2Worth = p2->getHand().evaluate();

                    //Player 1 Wins
                    if(p1Worth > p2Worth) {
                        cout << "Player " << p1->getID() + 1 << " Wins the Round!";
                        p1->addChips(pot);
                        return false;
                    }

                    //Player 2 Wins
                    else  if(p2Worth > p1Worth) {
                        cout << "Player " << p2->getID() + 1 << " Wins the Round!!";
                        p2->addChips(pot);
                        return false;
                     }
                    //Players Tied
                    else {
                        cout << "Players Tied Pot is Split";
                        p1->addChips(pot /2);
                        p2->addChips(pot / 2);
                        return false;
                    }
                }
                //Player 2 Folded
                else if(status == 0) {
                    p1->addChips(pot);
                    cout << "Player " << p1->getID() + 1 << " Wins the Round!";
                    return false;
                }
                //Player 1 Folded
                else if(status == 1){
                    p2->addChips(pot);
                    cout << "Player " << p2->getID() + 1 << "Wins the Round!";
                    return false;
                }
                else if(status == -2) {
                    return true;
                }
            }
            //Player 2 Folded
            else if(status == 0) {
                p1->addChips(pot);
                cout << "Player " << p1->getID() + 1 << " Wins the Round!";
                return false;
            }
            //Player 1 Folded
            else if(status == 1){
                p2->addChips(pot);
                cout << "Player " << p2->getID() + 1 << "Wins the Round!";
                return false;
            }
            //Human Wants to Quit
            else if(status == -2) {
                return true;
            }
        }
        else if(status == 0) {
            p1->addChips(pot);
            cout << "Player " << p1->getID() + 1 << " Wins the Round!";
            return false;
        }
            //Player 1 Folded
        else if(status == 1){
            p2->addChips(pot);
            cout << "Player " << p2->getID() + 1 << "Wins the Round!";
            return false;
        }
            //Human Wants to Quit
        else if(status == -2) {
            return true;
        }
    }
    else if(status == 0) {
        p1->addChips(pot);
        cout << "Player " << p1->getID() + 1 << " Wins the Round!";
        return false;
    }
        //Player 1 Folded
    else if(status == 1){
        p2->addChips(pot);
        cout << "Player " << p2->getID() + 1 << "Wins the Round!";
        return false;
    }
        //Human Wants to Quit
    else if(status == -2) {
        return true;
    }

    

}

int Game::betRound(Player *p1, Player *p2) {

}




//Deal the initial hand of the round
void Game::dealInitHand(Player *player1, Player *player2,Deck &deck) {
    player1->dealCard(deck.dealCard(false));
    player1->dealCard(deck.dealCard(true));
    player1->dealCard(deck.dealCard(true));

    player2->dealCard(deck.dealCard(false));
    player2->dealCard(deck.dealCard(true));
    player2->dealCard(deck.dealCard(true));

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
        cout << c.getName() << ", ";
    }

    cout << "\nChips: " << p1->getChips() << "\n \n";

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
        cout << c.getName() << ", ";
    }

    cout << "\nChips: " << p2->getChips() << "\n \n";
}