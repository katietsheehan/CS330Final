//
// Created by Katie Sheehan on 2019-05-05.
//

#ifndef TEXASHOLDEM_CARD_H
#define TEXASHOLDEM_CARD_H

#include <string>

using namespace std;

class Card {

public:
    Card(int n){
        this->suit = CalcSuit(n);
        this->rank = CalcRank(n);
    }

    string CalcSuit(int n);

    string CalcRank(int n);

    string GetSuit(){
        return this->suit;
    }
    string GetRank(){
        return this->rank;
    }
    string CardAsString(){
        return rank + " of "+ suit;
    }




private:
    string suit;
    string rank;

};


#endif //TEXASHOLDEM_CARD_H
