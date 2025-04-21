#ifndef BOTS_H
#define BOTS_H

#include "board.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Bots
{
private:
    string name;
    char symbol;
    unsigned short score;
    unsigned short WIN_COMBO;

public:
    Bots() : name("Arno"), symbol('X'), score(0), WIN_COMBO(3) { srand(time(nullptr)); };                                 // Seed RNG
    Bots(char sym, unsigned short mode) : name("Arno"), symbol(sym), score(0), WIN_COMBO(mode) { srand(time(nullptr)); }; // Seed RNG

    // methods
    void move(Boards &board);

    void change_score(unsigned short score) { this->score = score; };
};

#endif // BOTS_H
