#ifndef BOTS_H
#define BOTS_H

#include "board.h"
#include <string>
#include <vector>   // For move list
#include <utility>  // For pair
#include <limits>   // For numeric_limits
#include <cstdlib>
#include <ctime>

using namespace std;

struct Move {
    unsigned short row, col;
    int score;
};

class Bots
{
private:
    string name;
    char symbol;
    unsigned short score;
    unsigned short WIN_COMBO;
    int search_depth; // Add search depth for Minimax

    // Minimax helper functions
    Move find_best_move(Boards board); // Pass board by value for simulation
    int minimax(Boards board, int depth, bool is_maximizing, int alpha, int beta);
    int heuristic_evaluate(const Boards& board);
    vector<pair<unsigned short, unsigned short>> get_valid_moves(const Boards& board);
    // Keep the win check helper, useful for evaluation and maybe move ordering
    bool can_win_at(const Boards &board, unsigned short r, unsigned short c, char sym, unsigned short win_combo) const;

public:
    // Update constructors to accept/set search depth
    Bots() : name("Arno"), symbol('X'), score(0), WIN_COMBO(3), search_depth(5) { srand(time(nullptr)); };
    Bots(char sym, unsigned short mode) : name("Arno"), symbol(sym), score(0), WIN_COMBO(mode) {
        srand(time(nullptr));
        // Set depth based on mode (deeper for 3x3, shallower for 15x15 initially)
        search_depth = (mode == 3) ? 9 : 4; // Example: Max depth for 3x3, limited for 15x15
    };

    // methods
    void move(Boards &board); // This will now call find_best_move

    void change_score(unsigned short score) { this->score = score; };
    inline char get_symbol() const { return this->symbol; };
};

#endif // BOTS_H
