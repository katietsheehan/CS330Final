//
// Created by Katie Sheehan on 2019-05-05.
//

#ifndef TEXASHOLDEM_PLAYER_H
#define TEXASHOLDEM_PLAYER_H

#include <string>
#include <vector>
#include "Card.h"


using namespace std;


class Player{

public:
    Player(string name){
        this->name = name;
        this-> chips = 100;
    }

    string GetName(){
        return this->name;
    }
    vector<Card> GetHand(){
        return this-> hand;
    }

    void AddToHand(vector<Card>* deck);

    int GetChips(){
        return this->chips;
    }
    void SetChips(int c){
        this->chips = c;
    }

    int Showdown(vector<Card>* board);

private:
    string name;
    vector <Card> hand;
    int chips;


};


#endif //TEXASHOLDEM_PLAYER_H
