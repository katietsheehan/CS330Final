//
// Created by Katie Sheehan on 2019-05-05.
//

#include "Card.h"


using namespace std;

string Card::CalcSuit(int n) {
    int x = n/13;

    switch(x){
        case 0:
            return "Clubs";
        case 1:
            return "Diamonds";
        case 2:
            return "Hearts";
        case 3:
            return "Spades";
    }
}

string Card::CalcRank(int n) {
    int x = n%13;

    if(x == 0){
        return "Ace";
    }
    else if (0 < x && x < 10){
        x++;
        return to_string(x);
    }
    else{
        switch(x){
            case 10:
                return "Jack";
            case 11:
                return "Queen";
            case 12:
                return "King";
        }


    }


}