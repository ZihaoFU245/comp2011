#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include <string>
using namespace std;

class Players
{
private:
    string name;
    char symbol;
    unsigned short score;

public:
    Players() : name("NOT GIVEN") , symbol('O') , score(0) {};
    Players(string name , char sym) : name(name) , symbol(sym) , score(0) {};

    bool check_move(const Boards &board , unsigned short row , unsigned short col);
    bool move(Boards &board , unsigned short row , unsigned short col);
    // check condition is leave to game --- higher api

    inline void change_score(unsigned short score) {this->score = score;};
    inline char get_symbol() const { return this->symbol; }; // Add getter for symbol

};


#endif // PLAYER_H
