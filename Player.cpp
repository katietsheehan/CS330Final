//
// Created by Katie Sheehan on 2019-05-05.
//

#include "Player.h"

void Player::AddToHand(vector<Card>* deck) {
    for (int i = 0; i<2; i++){
        Card c = deck -> back();
        hand.push_back(c);
        deck -> pop_back();
    }
}

int Player::Showdown(vector<Card>* board){
    int samesuit = 0;
    int samerank = 0;
    int total = 0;
    for(Card c : *board){
        for(Card h : hand){
            if (c.GetSuit() == h.GetSuit()){
                samesuit += 1;
            }//if suit
            if (c.GetRank() == h.GetRank()){
                samerank += 1;
            }//if rank
        }//for hand
    }//for board
    total = samesuit + samerank;
    return(total);
}