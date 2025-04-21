#include "bots.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm> // For std::max, std::min, std::sort
#include <stdexcept> // Potentially for errors
#include <iostream>  // Include for cout/cerr
#include <set>       // For unique move generation

using namespace std;

// --- Helper Functions ---

// Check if a player has won on the current board state
// Note: This is slightly different from can_win_at, it checks the *current* state.
bool check_win_state(const Boards& board, char player_symbol, unsigned short win_combo) {
     unsigned int size = board.get_size();
    // Directions: horizontal, vertical, diagonal down-right, diagonal down-left
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for (unsigned short r = 0; r < size; ++r) {
        for (unsigned short c = 0; c < size; ++c) {
            if (board.get_position(r, c) == player_symbol) {
                for (int i = 0; i < 4; ++i) {
                    int count = 1;
                    for (int j = 1; j < win_combo; ++j) {
                        unsigned short nr = r + dr[i] * j;
                        unsigned short nc = c + dc[i] * j;
                        if (nr < size && nc < size && board.get_position(nr, nc) == player_symbol) {
                            count++;
                        } else {
                            break;
                        }
                    }
                    if (count >= win_combo) return true;
                }
            }
        }
    }
    return false;
}

// Check if the board is full (draw condition)
bool is_board_full(const Boards& board) {
    unsigned int size = board.get_size();
    for (unsigned short r = 0; r < size; ++r) {
        for (unsigned short c = 0; c < size; ++c) {
            if (board.get_position(r, c) == ' ') {
                return false;
            }
        }
    }
    return true;
}


// can_win_at: Checks if placing 'sym' at (r, c) would create a winning line
// (Implementation remains the same as before)
bool Bots::can_win_at(const Boards &board, unsigned short r, unsigned short c, char sym, unsigned short win_combo) const {
    // ... existing implementation ...
    unsigned int size = board.get_size();
    int count;
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        count = 1;
        for (int j = 1; j < win_combo; ++j) {
            unsigned short nr = r + dr[i] * j;
            unsigned short nc = c + dc[i] * j;
            if (nr < size && nc < size && board.get_position(nr, nc) == sym) count++; else break;
        }
        for (int j = 1; j < win_combo; ++j) {
            int pr = static_cast<int>(r) - dr[i] * j;
            int pc = static_cast<int>(c) - dc[i] * j;
            if (pr >= 0 && pc >= 0 && static_cast<unsigned short>(pr) < size && static_cast<unsigned short>(pc) < size &&
                board.get_position(static_cast<unsigned short>(pr), static_cast<unsigned short>(pc)) == sym) count++; else break;
        }
        if (count >= win_combo) return true;
    }
    return false;
}

// --- Optimized Move Generation ---
// Only considers empty cells adjacent to existing stones.
vector<pair<unsigned short, unsigned short>> Bots::get_valid_moves(const Boards& board) {
    set<pair<unsigned short, unsigned short>> potential_moves; // Use set to avoid duplicates
    unsigned int size = board.get_size();
    bool board_empty = true;

    // Define the search radius around existing stones (e.g., 1 for direct neighbors)
    const int radius = 1; // Check only immediately adjacent cells

    for (unsigned short r = 0; r < size; ++r) {
        for (unsigned short c = 0; c < size; ++c) {
            if (board.get_position(r, c) != ' ') {
                board_empty = false; // Found a stone
                // Check neighbors within the radius
                for (int dr = -radius; dr <= radius; ++dr) {
                    for (int dc = -radius; dc <= radius; ++dc) {
                        if (dr == 0 && dc == 0) continue; // Skip the stone itself

                        int nr_int = static_cast<int>(r) + dr;
                        int nc_int = static_cast<int>(c) + dc;

                        // Check bounds
                        if (nr_int >= 0 && nr_int < size && nc_int >= 0 && nc_int < size) {
                            unsigned short nr = static_cast<unsigned short>(nr_int);
                            unsigned short nc = static_cast<unsigned short>(nc_int);
                            // If the neighbor cell is empty, add it as a potential move
                            if (board.get_position(nr, nc) == ' ') {
                                potential_moves.insert({nr, nc});
                            }
                        }
                    }
                }
            }
        }
    }

    // If the board was completely empty, just return the center move
    if (board_empty) {
        unsigned short center = size / 2;
        if (center < size) { // Basic check
             return {{center, center}};
        } else {
            return {}; // Should not happen on valid board
        }
    }

    // Convert set to vector
    vector<pair<unsigned short, unsigned short>> moves(potential_moves.begin(), potential_moves.end());
    return moves;
}

// --- Heuristic Evaluation ---
// VERY BASIC - Needs significant improvement for 15x15 Gomoku
int Bots::heuristic_evaluate(const Boards& board) {
    char player_symbol = (symbol == 'X') ? 'O' : 'X';
    int score = 0;

    // Check for immediate win/loss states first
    if (check_win_state(board, symbol, WIN_COMBO)) {
        return 10000; // Bot wins - high positive score
    }
    if (check_win_state(board, player_symbol, WIN_COMBO)) {
        return -10000; // Player wins - high negative score
    }
    // No immediate win/loss, add more nuanced scoring here for 15x15
    // Example placeholder: Count potential wins for bot vs player
    // This is extremely naive for Gomoku. A real heuristic needs to analyze
    // patterns like open-threes, fours, threats, captures (if applicable), etc.
    // For 3x3, this basic win/loss check might be sufficient if depth is high enough.

    return score; // Return 0 if no immediate win/loss found by heuristic
}


// --- Minimax Implementation ---
int Bots::minimax(Boards board, int depth, bool is_maximizing, int alpha, int beta) {
    char player_symbol = (symbol == 'X') ? 'O' : 'X';

    // Check terminal states or depth limit
    if (check_win_state(board, symbol, WIN_COMBO)) return 10000 - (search_depth - depth); // Prioritize faster wins
    if (check_win_state(board, player_symbol, WIN_COMBO)) return -10000 + (search_depth - depth); // Prioritize blocking faster losses
    if (is_board_full(board)) return 0; // Draw
    if (depth == 0) return heuristic_evaluate(board); // Depth limit reached

    vector<pair<unsigned short, unsigned short>> valid_moves = get_valid_moves(board);

    if (is_maximizing) { // Bot's turn (Maximizer)
        int max_eval = numeric_limits<int>::min();
        // TODO: Implement move ordering here for better pruning
        for (const auto& move : valid_moves) {
            board.update_at(move.first, move.second, symbol); // Make move
            int eval = minimax(board, depth - 1, false, alpha, beta);
            board.update_at(move.first, move.second, ' '); // Undo move
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return max_eval;
    } else { // Player's turn (Minimizer)
        int min_eval = numeric_limits<int>::max();
        // TODO: Implement move ordering here
        for (const auto& move : valid_moves) {
            board.update_at(move.first, move.second, player_symbol); // Make move
            int eval = minimax(board, depth - 1, true, alpha, beta);
            board.update_at(move.first, move.second, ' '); // Undo move
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return min_eval;
    }
}

// --- Find Best Move using Minimax with Move Ordering ---
Move Bots::find_best_move(Boards board) { // Pass by value
    int best_val = numeric_limits<int>::min();
    Move best_move = {99, 99, best_val}; // Use invalid coords initially
    bool move_found = false;
    char player_symbol = (symbol == 'X') ? 'O' : 'X';
    unsigned short condition = this->WIN_COMBO;

    vector<pair<unsigned short, unsigned short>> valid_moves = get_valid_moves(board);

    if (valid_moves.empty()) {
        return best_move; // No moves possible
    }

    // --- Basic Move Ordering ---
    // 1. Check for immediate winning moves for the bot
    for (const auto& move : valid_moves) {
        if (can_win_at(board, move.first, move.second, symbol, condition)) {
            best_move.row = move.first;
            best_move.col = move.second;
            best_move.score = 10000; // Assign high score for immediate win
             cout << "Debug: Found immediate win move (" << best_move.row << "," << best_move.col << ")" << endl;
            return best_move; // Take the winning move immediately
        }
    }

    // 2. Check for immediate blocking moves against the player
    Move blocking_move = {99, 99, 0};
    bool block_found = false;
    for (const auto& move : valid_moves) {
        if (can_win_at(board, move.first, move.second, player_symbol, condition)) {
            // Found a potential block, store it but continue searching minimax
            // in case there's an even better move (like setting up a double threat)
            blocking_move.row = move.first;
            blocking_move.col = move.second;
            block_found = true;
             cout << "Debug: Found potential blocking move (" << blocking_move.row << "," << blocking_move.col << ")" << endl;
            // Don't return immediately, let minimax evaluate further, but keep this as a candidate
            break; // Found one block, that's enough for this simple check
        }
    }

    // --- Run Minimax on remaining moves ---
    int alpha = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();

    // Optional: Sort moves based on heuristic score? (More advanced ordering)

    for (const auto& move : valid_moves) {
        // Skip the blocking move if we already evaluated it implicitly? No, evaluate all.
        unsigned int board_size_local = board.get_size();
        if (move.first >= board_size_local || move.second >= board_size_local || board.get_position(move.first, move.second) != ' ') {
             cerr << "Warning: Skipping invalid move in find_best_move loop (" << move.first << "," << move.second << ")." << endl;
             continue;
        }

        board.update_at(move.first, move.second, symbol); // Make move
        int move_val = minimax(board, search_depth -1, false, alpha, beta); // Start recursion
        board.update_at(move.first, move.second, ' '); // Undo move

        if (!move_found || move_val > best_val) {
            best_val = move_val;
            best_move.row = move.first;
            best_move.col = move.second;
            best_move.score = best_val;
            move_found = true;
        }
         alpha = max(alpha, best_val);
    }

    // If minimax didn't find a move better than a potential block, consider the block
    // A simple heuristic: if best score is low (e.g. <= 0) and a block exists, take the block.
    // This prevents choosing a neutral move when a block is necessary.
    if (block_found && best_val <= 0) { // Adjust threshold as needed
         cout << "Debug: Choosing blocking move (" << blocking_move.row << "," << blocking_move.col << ") over minimax score " << best_val << endl;
        best_move = blocking_move;
        best_move.score = 0; // Assign neutral score to block for consistency? Or keep minimax score? Let's keep it simple.
        move_found = true;
    }


     if (!move_found && !valid_moves.empty()) {
         // Fallback if no move was selected (should be rare now)
         best_move.row = valid_moves[0].first;
         best_move.col = valid_moves[0].second;
         best_move.score = best_val; // Keep the score found
         move_found = true;
     }

    return best_move;
}


// --- Main move function ---
void Bots::move(Boards &board)
{
    // Use Minimax to find the best move
    Move best = find_best_move(board); // Pass current board state

    // Output the bot's chosen move coordinates
    cout << "Bot decision: Placing " << symbol << " at (" << best.row << ", " << best.col << ") with score " << best.score << endl;

    // Check if the returned move is valid (within bounds and empty)
    unsigned int size = board.get_size(); // Get size from the actual board reference
    if (best.row < size && best.col < size && board.get_position(best.row, best.col) == ' ') {
         board.update_at(best.row, best.col, symbol);
    } else {
         // Fallback: Minimax/find_best_move failed to return a valid, empty cell.
         vector<pair<unsigned short, unsigned short>> empty_cells;
         // Use the optimized generator for fallback too, but if that fails, try all empty cells
         empty_cells = get_valid_moves(board);
         if (empty_cells.empty()) { // If optimized gives nothing, try brute force
             unsigned int full_size = board.get_size();
             for(unsigned short r=0; r<full_size; ++r) for(unsigned short c=0; c<full_size; ++c) if(board.get_position(r,c)==' ') empty_cells.push_back({r,c});
         }

         if (!empty_cells.empty()) {
            // Output a warning to stderr
            cerr << "Warning: Minimax failed or returned invalid/occupied move ("
                 << best.row << "," << best.col << " score=" << best.score
                 << "). Falling back to random move from available." << endl;
            int random_index = rand() % empty_cells.size();
            // Output the fallback move
            cout << "Bot fallback: Placing " << symbol << " randomly at (" << empty_cells[random_index].first << ", " << empty_cells[random_index].second << ")" << endl;
            board.update_at(empty_cells[random_index].first, empty_cells[random_index].second, symbol);
         } else {
              cerr << "Error: Bot cannot move, no empty cells found even in fallback!" << endl;
         }
    }
}