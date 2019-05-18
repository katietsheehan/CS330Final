#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "Card.h"
#include "Player.h"


using namespace std;

void MakeDeck(vector<Card>* deck){
    for(int i = 0; i < 52; i++){
        deck -> push_back(Card(i));
    }
    //return deck;
}
string Name(){
    string n;
    cout << "Enter your name"<<endl;
    cin >> n;
    return n;
}
void Deal(vector<Player*> p,vector<Card>* d){
    for(Player *player : p){
        player -> AddToHand(d);
    }
}
void Blinds(int* pot,vector<Player*> p){
    p.at(0) -> SetChips(p.at(0)->GetChips()-1);
    *pot += 1;
    p.at(1) -> SetChips(p.at(1)->GetChips()-2);
    *pot += 2;

}

void FirstBet(vector<Player*> p, int* pot, vector<Card>* burn,vector<Player*>* _p);
void CPUFirstBet(vector<Player*> p, int* pot, vector<Card>* burn);
void FollowingBet(vector<Player*> p, int* pot, vector<Card>* burn,vector<Player*>* _p);
void CPUFollowingBet(vector<Player*> p, int* pot, vector<Card>* burn);


int main() {

    //Prep/Setup for game

    //players
    Player cpu = Player("CPU_1");
    Player cpu2 = Player("CPU_2");
    Player p1 = Player(Name());
    cout << endl;
    vector<Player*> players = {&cpu, &cpu2, &p1};
    vector<Player*>* _players = &players;
    //deck
    vector<Card> deck;
    vector<Card>* d = & deck;
    MakeDeck(d);
    random_shuffle(begin(deck), end(deck));
    vector<Card> burn;
    vector<Card>* b = &burn;
    vector<Card> board;
    vector<Card>* b0 = &board;
    //blinds
    int p = 0;
    int* pot = &p;
    Blinds(pot, players);

    //Deal
    Deal(players,d);

    cout<< p1.GetName() << ", your hand is: "<< endl;
    for(Card c : p1.GetHand()){
        cout << c.CardAsString()<< endl;
    }

    FirstBet(players, pot, b, _players);
    CPUFirstBet(players, pot, b);// cpu does not have option to fold
    cout<< "the pot is "<< p<<endl;
    cout<< endl;

    if (players.back()->GetName() == p1.GetName()){//checks that player is still in the game
        b -> push_back(d -> back());
        d -> pop_back(); //burn card
        for(int i =0; i<3; i++){
            b0 -> push_back(d -> back());
            d -> pop_back();
        }
        cout<< "The flop is: "<< endl;
        for(Card c : board){
            cout<< c.CardAsString()<< endl;
        }
        cout<< endl;

        CPUFollowingBet(players, pot, b);   // cpu does not have option to fold
        FollowingBet(players, pot, b, _players);
        if (players.back()->GetName() == p1.GetName()){
            b -> push_back(d -> back());
            d -> pop_back(); //burn card
            b0 -> push_back(d -> back());
            d -> pop_back();
            cout<< "The turn is: "<< endl;
            for(Card c : board){
                cout<< c.CardAsString()<< endl;
            }
            cout<< endl;

            CPUFollowingBet(players, pot, b);   // cpu does not have option to fold
            FollowingBet(players, pot, b, _players);
            if (players.back()->GetName() == p1.GetName()){
                b -> push_back(d -> back());
                d -> pop_back(); //burn card
                b0 -> push_back(d -> back());
                d -> pop_back();
                cout<< "The river is: "<< endl;
                for(Card c : board){
                    cout<< c.CardAsString()<< endl;
                }
                cout<< endl;
                cout<<"This is the final betting round."<<endl;
                CPUFollowingBet(players, pot, b);   // cpu does not have option to fold
                FollowingBet(players, pot, b, _players);

                if (players.back()->GetName() == p1.GetName()){
                    cout<< "Showdown"<< endl;
                    Player* winner;
                    if (cpu.Showdown(b) > cpu2.Showdown(b) && cpu.Showdown(b) > p1.Showdown(b)) {
                        winner = &cpu;
                    }
                    else if(cpu2.Showdown(b) > cpu.Showdown(b) && cpu2.Showdown(b) > p1.Showdown(b)) {
                        winner = &cpu2;
                    }
                    else{
                        winner = &p1;
                    }
                    cout<< "the winner gets " << p << " chips"<< endl;
                    for(int i = 0; i< 2; i++){
                        cout<< players.at(i) -> GetName()<< " has: "<<endl;
                        for(Card c : players.at(i) -> GetHand()){
                            cout<< c.CardAsString()<<endl;
                        }
                    }
                    cout<< endl;
                    winner -> SetChips(winner -> GetChips() + p);
                    cout<< "the winner of the hand is "<< winner -> GetName() << endl;

                }
            }

        }
    }

    //cout<< "the pot is "<< p<<endl;




    return 0;
}

void FirstBet(vector<Player*> p, int* pot, vector<Card>* b,vector<Player*>* _p){
    string n;
    cout << p.at(2) -> GetName()<< " is first to act."<< endl;
    cout << "Would you like to call, raise, or fold?"<< endl;
    cin >> n;
    int choice = 0;
    if (n == "call" || n == "Call"){
        choice = 1;
    }
    else if (n == "raise" || n == "Raise"){
        choice = 2;
    }
    else if (n == "fold" || n == "Fold"){
        choice = 3;
    }

    switch(choice){
        case 1:
            p.at(2) -> SetChips(p.at(2)->GetChips()-2);
            *pot += 2;
            break;
        case 2:
            int r;
            cout << "What would you like to raise?"<<endl;
            cin >> r;
            p.at(2) -> SetChips(p.at(2)->GetChips()-r);
            *pot += r;
            break;
        case 3:
            for (int i = 0; i<2; i++){
                b -> push_back(p.at(2)->GetHand().at(i));
                p.at(2)->GetHand().pop_back();
            }
            _p -> erase(p.end());
            break;
        default:
            p.at(2) -> SetChips(p.at(2)->GetChips()-2);
            *pot += 2;
            break;
    }
}
void CPUFirstBet(vector<Player*> p, int* pot, vector<Card>* burn){
    int choice;
    srand (time(0));
    for(int i= 0; i<2; i++){
        choice = rand()%2;
        switch(choice){
            case 0:
                cout<< p.at(i) -> GetName() << " has called."<<endl;
                p.at(i) -> SetChips(p.at(i)->GetChips()-2);
                *pot += 2;
                break;
            case 1:
                cout<< p.at(i) -> GetName() << " has raised."<<endl;
                p.at(2) -> SetChips(p.at(2)->GetChips()-4);
                *pot += 4;
                break;
        }

    }
}
void FollowingBet(vector<Player*> p, int* pot, vector<Card>* b,vector<Player*>* _p){
    string n;
    cout << p.at(2) -> GetName()<< " is acting"<< endl;
    cout << "Would you like to call, raise, check, or fold?"<< endl;
    cin >> n;
    int choice = 0;
    if (n == "call" || n == "Call"){
        choice = 1;
    }
    else if (n == "raise" || n == "Raise"){
        choice = 2;
    }
    else if (n == "fold" || n == "Fold"){
        choice = 3;
    }
    else if (n == "check" || n == "Check"){
        choice = 4;
    }

    switch(choice){
        case 1:
            p.at(2) -> SetChips(p.at(2)->GetChips()-2);
            *pot += 2;
            break;
        case 2:
            int r;
            cout << "What would you like to raise?"<<endl;
            cin >> r;
            p.at(2) -> SetChips(p.at(2)->GetChips()-r);
            *pot += r;
            break;
        case 3:
            for (int i = 0; i<2; i++){
                b -> push_back(p.at(2)->GetHand().at(i));
                p.at(2)->GetHand().pop_back();
            }
            _p -> erase(p.end());
            break;
        case 4:
            break;
        default:
            p.at(2) -> SetChips(p.at(2)->GetChips()-2);
            *pot += 2;
            break;
    }

}
void CPUFollowingBet(vector<Player*> p, int* pot, vector<Card>* burn){
    int choice;
    srand (time(0));
    for(int i= 0; i<2; i++){
        cout<< p.at(i) -> GetName() <<" is acting."<< endl;
        choice = rand()%3;
        switch(choice){
            case 0:
                cout<< p.at(i) -> GetName() << " has called."<<endl;
                p.at(i) -> SetChips(p.at(i)->GetChips()-2);
                *pot += 2;
                break;
            case 1:
                cout<< p.at(i) -> GetName() << " has raised."<<endl;
                p.at(2) -> SetChips(p.at(2)->GetChips()-4);
                *pot += 4;
                break;
            case 2:
                cout<< p.at(i) -> GetName() << " has checked."<<endl;
                break;
        }
        cout<<endl;

    }
}

