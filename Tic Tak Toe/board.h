#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include "utils.h"
using namespace std;

class Boards
{
private:
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    unsigned int size{};

    // initialize board
    void initBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], unsigned int size, char fillin = ' ');

public:
    Boards();
    Boards(unsigned int size);

    unsigned int get_size() const {return this->size;};
    char get_position(unsigned int row , unsigned int col) const;
    void update_at(unsigned int row , unsigned int col , char sym);


    void printBoard();

    void ResetBoard();
    void change_size(unsigned int size) {this->size = size; };
};



#endif // BOARD_H