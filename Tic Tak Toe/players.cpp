#include "player.h"
using namespace std;

bool Players::check_move(const Boards &board, unsigned short row, unsigned short col)
{
    if (row >= board.get_size() || col >= board.get_size())
        return false;

    if (board.get_position(row, col) != ' ')
        return false;

    return true;
}

bool Players::move(Boards &board, unsigned short row, unsigned short col)
{
    if (!Players::check_move(board, row, col))
        return false;

    board.update_at(row, col, this->symbol);
    return true;
}

