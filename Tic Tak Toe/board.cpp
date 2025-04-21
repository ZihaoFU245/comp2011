#include "board.h"
#include <iostream>
using namespace std;


// helper functions
void __getBoard__(const char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size)
{
    // Helper lambda to print the horizontal separator line dynamically based on size
    auto printHorizontalLine = [size]() {
        for (int k = 0; k < size; ++k) {
            std::cout << "+---"; // Print "+---" for each column
        }
        std::cout << "+" << std::endl; // Print the final "+" and a newline
    };

    for (int i = 0; i < size; i++)
    {
        // Print the separator line before each row
        printHorizontalLine();

        // Print the row cells
        std::cout << "| "; // Print the leading border for the row
        for (int j = 0; j < size; j++)
        {
            // Print the cell content followed by a separator
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl; // End the line after printing all cells in the row
    }

    // Print the final bottom border line after the last row
    printHorizontalLine();
}


// private funcs
void Boards::initBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] , unsigned int size , char fillin)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = fillin; // initialize the board with empty spaces
        }
    }
}

// public funcs
Boards::Boards()
{
    this->size = 3;
    initBoard(board , size , ' ');
}

Boards::Boards(unsigned int size)
{
    this->size = size;
    initBoard(board , size , ' ');
}

void Boards::printBoard()
{
    __getBoard__(this->board , this->size);    
}

char Boards::get_position(unsigned int row , unsigned int col) const
{
    return this->board[row][col];
}

void Boards::update_at(unsigned int row , unsigned int col , char sym)
{
    this->board[row][col] = sym;
}

void Boards::ResetBoard()
{
    initBoard(this->board , this->size , ' ');
}