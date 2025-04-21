#include "bots.h"
#include <cstdlib>
#include <ctime>
#include <vector> // Include vector for storing empty cells
#include <utility> // Include utility for std::pair
using namespace std;

// helper functions

// Checks if placing 'sym' at (r, c) results in a win condition
bool check_win_at(const Boards &board, unsigned short r, unsigned short c, char sym, unsigned short win_combo) {
    unsigned int size = board.get_size();
    int count;

    // Directions: horizontal, vertical, diagonal down-right, diagonal down-left
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        count = 1; // Count the potential move itself

        // Check in one direction
        for (int j = 1; j < win_combo; ++j) {
            unsigned short nr = r + dr[i] * j;
            unsigned short nc = c + dc[i] * j;
            if (nr < size && nc < size && board.get_position(nr, nc) == sym) {
                count++;
            } else {
                break;
            }
        }

        // Check in the opposite direction
        for (int j = 1; j < win_combo; ++j) {
            // Use int for intermediate calculation to handle potential negative results before comparison
            int pr = static_cast<int>(r) - dr[i] * j;
            int pc = static_cast<int>(c) - dc[i] * j;
            if (pr >= 0 && pc >= 0 && pr < size && pc < size && board.get_position(static_cast<unsigned short>(pr), static_cast<unsigned short>(pc)) == sym) {
                 count++;
            } else {
                break;
            }
        }

        if (count >= win_combo) {
            return true; // Found a winning line
        }
    }

    return false; // No winning line found for this move
}


// main functions

void Bots::move(Boards &board)
{
    unsigned int size = board.get_size();
    char bot_symbol = this->symbol;
    char player_symbol = (bot_symbol == 'X') ? 'O' : 'X';
    unsigned short condition = this->WIN_COMBO;
    int best_r = -1, best_c = -1;

    // 1. Check if bot can win in the next move
    for (unsigned short r = 0; r < size; ++r) {
        for (unsigned short c = 0; c < size; ++c) {
            if (board.get_position(r, c) == ' ') {
                // Temporarily place bot symbol (not really, just check condition)
                if (check_win_at(board, r, c, bot_symbol, condition)) {
                    board.update_at(r, c, bot_symbol);
                    return; // Bot wins
                }
            }
        }
    }

    // 2. Block the player if they can win in the next move
    for (unsigned short r = 0; r < size; ++r) {
        for (unsigned short c = 0; c < size; ++c) {
            if (board.get_position(r, c) == ' ') {
                 // Temporarily place player symbol (not really, just check condition)
                if (check_win_at(board, r, c, player_symbol, condition)) {
                    board.update_at(r, c, bot_symbol); // Block player
                    return;
                }
            }
        }
    }

    // 3. If no immediate win or block, find all empty spots and choose randomly
    vector<pair<unsigned short, unsigned short>> empty_cells;
    for (unsigned short r = 0; r < size; ++r) {
        for (unsigned short c = 0; c < size; ++c) {
            if (board.get_position(r, c) == ' ') {
                empty_cells.push_back({r, c});
            }
        }
    }

    if (!empty_cells.empty()) {
        int random_index = rand() % empty_cells.size();
        best_r = empty_cells[random_index].first;
        best_c = empty_cells[random_index].second;
        board.update_at(best_r, best_c, bot_symbol);
    }
    // If empty_cells is empty, it means the board is full, although this function
    // should ideally not be called in that state by the game logic.
}