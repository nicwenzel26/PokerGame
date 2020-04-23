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
bool RF;

bool Game::playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag) {
    //TODO ADD GAME FUNCTIONALITY
    Player*player1;
    Player* player2;

    RF = reportFlag;

    //Setting fake data before set
    HumanPlayer human = HumanPlayer(-1, -1);
    AlphaPlayer alpha = AlphaPlayer(-1, -1);

    HumanPlayer human2 = HumanPlayer(-1,-1);
    AlphaPlayer alpha2 = AlphaPlayer(-1,-1);

    Deck deck = Deck();
    bh = BetHistory();


    //Set current round to 1
    int numRounds = 1;
    //Setting the quit condition
    bool quit = false;

    if(p0 == HUMAN && p1 == ALPHA) {
        human = HumanPlayer(0, chips0);
        alpha = AlphaPlayer(1, chips1);

        player1 = &human;
        player2 = &alpha;
    }
    else if(p0 == HUMAN && p1 == HUMAN) {
        human = HumanPlayer(0,chips1);
        human2 = HumanPlayer(1,chips1);
        player1 = &human;
        player2 = &human2;
    }
    else if (p0 == ALPHA && p1 == HUMAN){
        alpha = AlphaPlayer(0, chips0);
        human = HumanPlayer(1, chips1);
        player1 = &alpha;
        player2 = &human;
    }

    else  {
        alpha = AlphaPlayer(0, chips0);
        alpha2 = AlphaPlayer(1, chips1);
        player1 = &alpha;
        player2 = &alpha2;
    }

    //While there are still round to play and while the player doesn't want to quit.
    while(numRounds <= 20 && !quit) {
        //Start of Round
        if(RF){
            cout << "\nRound: " << numRounds << "\n";
        }
        //Add chips from each player.
        player1->addChips(-10);
        player2->addChips(-10);

        //Add chips from each player to the pot;
        pot += 20;

        //Reset the decks cards
        deck.resetDeck();

        //Initial Empty bet.
        bh.addBet(Bet(-1, -1));

        //Deal the initial hand of the round
        dealInitHand(player1, player2, deck);

        //Printing the visible hands of bother of the players
        if(RF) {
            printVisable(player1, player2);
        }


        //Alternate who starts the betting rounds
        if(numRounds % 2 != 0) {
            quit = playHand(player1, player2, deck, pot, bh);
        }
        else {
            quit  = playHand(player2, player1, deck, pot, bh);
        }

        if(quit) {
            return true;
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
    return true;
}


bool Game::playHand(Player *p1, Player *p2, Deck &deck, int &pot, BetHistory &bh) {
    int status;
    //First betting round
    status  = betRound(p1, p2, bh, pot);
    //Both players are still in the game
    if(status == -1) {
        bh.clearHistory();
        p1->dealCard(deck.dealCard(true));
        p2->dealCard(deck.dealCard(true));
        if(RF) printVisable(p1, p2);
        bh.addBet(Bet(-1,-1));
        status = betRound(p1, p2, bh, pot);
        //Both players are still in the game
        //Deal Second Card
        if(status == -1) {
            p1->dealCard(deck.dealCard(true));
            p2->dealCard(deck.dealCard(true));
            bh.clearHistory();
            bh.addBet(Bet(-1,-1));
            if(RF) printVisable(p1, p2);
            status = betRound(p1, p2, bh, pot);
            //Both players are still in the game
            //Final betting Round
            if(status == -1) {
                p1->dealCard(deck.dealCard(true));
                p2->dealCard(deck.dealCard(true));
                bh.clearHistory();
                bh.addBet(Bet(-1,-1));
                if(RF) printVisable(p1, p2);
                status = betRound(p1, p2, bh, pot);
                //Both players are still in the game
                if(status == -1){
                    //Flipping the hidden cards
                    if(RF) cout << "Flipping the hidden cards: \n";
                    p1->getHand().getCard(0).setFaceUp(true);
                    p2->getHand().getCard(0).setFaceUp(true);
                    if(RF) printVisable(p1, p2);
                    int p1Worth = p1->getHand().evaluate();
                    int p2Worth = p2->getHand().evaluate();

                    //Player 1 Wins
                    if(p1Worth > p2Worth) {
                        if(RF) cout << "Player " << p1->getID() + 1 << " Wins the Round!\n";
                        p1->addChips(pot);
                        return false;
                    }

                    //Player 2 Wins
                    else  if(p2Worth > p1Worth) {
                        if(RF) cout << "Player " << p2->getID() + 1 << " Wins the Round!!\n";
                        p2->addChips(pot);
                        return false;
                     }
                    //Players Tied
                    else {
                        if(RF) cout << "Players Tied Pot is Split\n";
                        p1->addChips(pot /2);
                        p2->addChips(pot / 2);
                        return false;
                    }
                }
                //Player 2 Folded
                else if(status == 0) {
                    p1->addChips(pot);
                    if(RF) cout << "Player " << p1->getID() + 1 << " Wins the Round!\n";
                    return false;
                }
                //Player 1 Folded
                else if(status == 1){
                    p2->addChips(pot);
                    if(RF) cout << "Player " << p2->getID() + 1 << " Wins the Round!\n";
                    return false;
                }
                else if(status == -2) {
                    return true;
                }
            }
            //Player 2 Folded
            else if(status == 0) {
                p1->addChips(pot);
                if(RF) cout << "Player " << p1->getID() + 1 << " Wins the Round!\n";
                return false;
            }
            //Player 1 Folded
            else if(status == 1){
                p2->addChips(pot);
                if(RF) cout << "Player " << p2->getID() + 1 << " Wins the Round!\n";
                return false;
            }
            //Human Wants to Quit
            else if(status == -2) {
                return true;
            }
        }
        else if(status == 0) {
            p1->addChips(pot);
            if(RF) cout << "Player " << p1->getID() + 1 << " Wins the Round!\n";
            return false;
        }
            //Player 1 Folded
        else if(status == 1){
            p2->addChips(pot);
            if(RF) cout << "Player " << p2->getID() + 1 << "Wins the Round!\n";
            return false;
        }
            //Human Wants to Quit
        else if(status == -2) {
            return true;
        }
    }
    else if(status == 0) {
        p1->addChips(pot);
        if(RF) cout << "Player " << p1->getID() + 1 << " Wins the Round!\n";
        return false;
    }
        //Player 1 Folded
    else if(status == 1){
        p2->addChips(pot);
        if(RF) cout << "Player " << p2->getID() + 1 << " Wins the Round!\n";
        return false;
    }
        //Human Wants to Quit
    else if(status == -2) {
        return true;
    }



}

int Game::betRound(Player *p1, Player *p2, BetHistory &bh, int &pot) {
    bool keepBetting = true;
    Hand p1Hand = p1->getHand().getVisible();
    Hand p2Hand = p2->getHand().getVisible();

    int p1Bet = 0;
    int p2Bet = 0;

    while(keepBetting) {
        int lastBet = bh.getBet(bh.getCount() - 1).getAmount();
        bool p1CanRaise = p1->getChips() >= lastBet + 10;
        p1Bet = p1->getBet(p2Hand, bh, lastBet, p1CanRaise, pot);
        if(p1Bet == 0 && lastBet != -1 ) {
            if(RF) cout << "Player " << p1->getID() + 1 << " Folds\n";
            return p2->getID();
        }
        else if(p1Bet == 0 && lastBet == -1) {
            if(RF) cout << "Player " << p1->getID() + 1 << " Calls\n";
            bh.addBet(Bet(p1Bet, p1->getID()));
        }
        else if(p1Bet == -1) return -2;
        else if(p1Bet == lastBet) {
            pot += p1Bet;
            p1->addChips(-p1Bet);
            bh.addBet(Bet(p1Bet, p1->getID()));
            if(RF) cout << "Player " << p1->getID() + 1 << " Calls\n";
            return -1;
        }
        else {
            pot += p1Bet;
            p1->addChips(-p1Bet);
            bh.addBet(Bet(p1Bet, p1->getID()));
            if(RF) cout << "Player " << p1->getID() + 1 << " Raises\n";
        }
        int p2Chips = p2->getChips();
        bool p2CanRaise = p2Chips >= p1Bet + 10;
        p2Bet = p2->getBet(p1Hand, bh, p1Bet, p2CanRaise, pot);
        if(p2Bet == 0) {
            if(RF) cout << "Player " << p2->getID() + 1 << " Folds\n";
            return p1->getID();
        }
        else if(p2Bet == -1) return -2;
        else if(p2Bet == p1Bet) {
            pot+= p2Bet;
            p2->addChips(-p2Bet);
            bh.addBet(Bet(p2Bet, p2->getID()));
            if(RF) cout << "Player " << p2->getID() + 1 << " Calls\n";
            return -1;
        }
        else{
            pot += p2Bet;
            p2->addChips(-p2Bet);
            bh.addBet(Bet(p2Bet, p2->getID()));
            if(RF) cout << "Player " << p2->getID() + 1 << " Raises\n";
        }
    }

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