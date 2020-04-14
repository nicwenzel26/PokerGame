//
// Created by Nic on 4/3/20.
//

#include "AlphaPlayer.h"
#include <iostream>

AlphaPlayer::AlphaPlayer(int id, int chips): Player(id, chips) {

}

int AlphaPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) {
    int delta = this->getHand().evaluate() - opponent.evaluate();
    bool lastRound = false;

    //If the hand size is 5 then we are in the last betting round
    if(opponent.getCount() == 5) lastRound = true;
    //If there have been no previous bets

    if(!lastRound) {
        if(bet2player == -1) {
            //Raise 10
            if(delta > 10 && canRaise) {
                cout << "Alpha player raises 10!\n";
                return 10;
            }
                //Raise 5
            else if(delta > 5 && canRaise) {
                cout << "Alpha player raises 5!\n";
                return 5;
            }

                //Raise 1
            else if (delta > 0 && canRaise) {
                cout << "Alpha player raises 1!\n";
                return 1;
            }

                //Else call
            else {
                cout << "Alpha player calls!\n";
                return 0;
            }

        }

        else {
            //Calculating pot factor
            int potFactor = pot / 10;
            int previousBet = bh.getBet(bh.getCount() - 2).getAmount();

            //If the last player called
            if((bet2player == 0 && previousBet == -1) || bet2player == previousBet) {
                //Raise 10
                if(delta > 5-potFactor && canRaise) {
                    cout << "Alpha player raises 10!\n";
                    return 10 + bet2player;
                }
                    //Raise 1
                else if(delta > 0 && canRaise) {
                    cout << "Alpha player raises 1!\n";
                    return 1 + bet2player;
                }

                    //Call
                else {
                    cout << "Alpha player calls.\n";
                    return bet2player;
                }
            }

                //If prior bet is a raise and in range of pot factor
            else if(bet2player > previousBet && bet2player < 1 + potFactor*2) {
                //raise 10
                if(delta > 8 - potFactor && canRaise) {
                    cout << "Alpha player raises 10!\n";
                    return 10 + bet2player;
                }
                    //Raise 1
                else if (delta > -2 - potFactor && canRaise) {
                    cout << "Alpha player raises 1!\n";
                    return 1 + bet2player;
                }
                    //Call
                else if(delta > -4 - potFactor) {
                    cout << "Alpha player calls!\n";
                    return bet2player;
                }
            }

            else {
                //Raise 10
                if(delta  > 10 - potFactor && canRaise) {
                    cout << "Alpha player raises 10!\n";
                    return 10 + bet2player;
                }
                    //Raise 1
                else if(delta  > 0 -potFactor && canRaise) {
                    cout << "Alpha player raises 1!\n";
                    return 1 + bet2player;
                }
                    //Call
                else if(delta  > -2 - potFactor) {
                    cout << "Alpha player calls.\n";
                    return bet2player;
                }
                    //Fold
                else {
                    cout << "Alpha player folds!\n";
                    return 0;
                }
            }
        }
    }

    //It is the last betting round
    else {

        //If there are no prior bets
        if(bet2player == -1) {
            //Raise 10
            if(delta  >  10 && canRaise ) {
                cout << "Alpha player raises 10!\n";
                return 10;
            }
            //Raise 5
            else if(delta  > 5 && canRaise) {
                cout << "Alpha player raises 5!\n";
                return 5;
            }
            //Call
            else {
                cout << "Alpha player calls!\n";
                return 0;
            }
        }

        else {
            int previousBet = bh.getBet(bh.getCount() - 2).getAmount();
            int potFactor = pot / 10;

            if((bet2player == 0 && previousBet == -1) || bet2player == previousBet) {
                //Raise 10
                if(delta > 10 - potFactor && canRaise) {
                    cout << "Alpha player raises 10!\n";
                    return bet2player + 10;
                }

                else {
                    cout << "Alpha player calls.\n";
                    return bet2player;
                }
            }

            else if(bet2player > previousBet && bet2player < 1 + potFactor*2) {

                //Raise 10
                if(delta > 6-potFactor && canRaise) {
                    cout << "Alpha player raises 10!\n";
                    return bet2player + 10;
                }

                //Call
                else if(delta > 2) {
                    cout << "Alpha player calls.\n";
                    return bet2player;
                }

                //Fold
                else {
                    cout << "Alpha player folds.\n";
                    return 0;
                }
            }

            else {
                //Raise 10
                if(delta > 8 - potFactor && canRaise) {
                    cout << "Alpha player raises 10.\n";
                    return bet2player + 10;
                }

                //Call
                else if(delta  > 4) {
                    cout << "Alpha player calls.\n";
                    return bet2player;
                }

                //Fold
                else {
                    cout << "Alpha player folds.\n";
                    return 0;
                }
            }
        }

    }
   return -1;
}