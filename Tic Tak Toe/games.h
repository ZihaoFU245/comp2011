#ifndef GAMES_H
#define GAMES_H

#include "utils.h"
#include "player.h"
#include "board.h"
#include "bots.h"
#include <string>
#include <vector> // For get_board_state
#include <utility> // For get_scores
#include <stdexcept> // For exceptions

using namespace std;

enum class GameMode { PLAYER_VS_PLAYER, PLAYER_VS_BOT };
enum class GameState { ONGOING, DRAW, WIN };

class Games
{
private:
    Boards board;
    Players player_uno;
    Players player_dos; // Used in PvP mode
    Bots bot;           // Used in PvB mode
    GameMode mode;
    unsigned short target_wins; // 2 for Bo3, 3 for Bo5
    unsigned short player_uno_wins;
    unsigned short opponent_wins; // Player 2 or Bot wins
    unsigned short win_combo;     // 3 for 3x3, 5 for 15x15
    char current_player_symbol;
    bool match_over;
    char match_winner_symbol; // ' ' if no winner yet or draw match (unlikely BoX)
    GameState current_round_state;
    char round_winner_symbol; // Symbol of the round winner, ' ' for draw/ongoing

    // Private helper methods
    void switch_turn();
    bool check_win_condition(char player_symbol); // Checks if player_symbol won the round
    bool check_draw_condition(); // Checks if the current round is a draw
    void update_state_after_move(bool move_made, char symbol); // Updates round/match state
    void start_new_round_internal(); // Internal logic for starting a round

public:
    // --- Constructors ---
    // Constructor for Player vs Bot
    Games(string game_type, string match_type, string player_name, char player_symbol);
    // Constructor for Player vs Player
    Games(string game_type, string match_type, string p1_name, char p1_sym, string p2_name, char p2_sym);

    // --- Game Control & Moves ---
    // Attempts to place the current player's symbol at (row, col).
    // Returns true if the move is valid and made, false otherwise.
    // Throws logic_error if not a human player's turn or game is over.
    bool make_player_move(unsigned short row, unsigned short col);

    // Makes the bot's move.
    // Returns true if the move was made, false otherwise (e.g., board full).
    // Throws logic_error if not PvB mode or not bot's turn or game is over.
    bool make_bot_move();

    // Resets the board for a new round, updates who starts (optional alternation).
    // Should be called by the external layer when is_round_over() is true and is_match_over() is false.
    void start_new_round();

    // --- State Query Methods ---
    vector<vector<char>> get_board_state() const; // Returns a copy of the board
    char get_current_player_symbol() const { return current_player_symbol; }
    bool is_round_over() const { return current_round_state != GameState::ONGOING; }
    char get_round_winner() const { return round_winner_symbol; } // Returns winner symbol or 'D' for Draw, ' ' for ongoing
    bool is_match_over() const { return match_over; }
    char get_match_winner() const { return match_winner_symbol; } // Returns winner symbol or ' '
    pair<unsigned short, unsigned short> get_scores() const { return {player_uno_wins, opponent_wins}; }
    GameMode get_game_mode() const { return mode; }
    unsigned short get_win_combo() const { return win_combo; }

    // Removed default constructor as it's less useful with match types
    // Games();
    // Removed old constructors
    // Games(string game_type, string player_name, char symbol);
    // Games(string game_type, string p1_name, char p1_sym, string p2_name, char p2_sym);

    // Removed check_win - replaced by specific round/match checks
    // bool check_win();
    // Removed start_game - logic moved to external layer interacting with API methods
    // void start_game();
};

#endif //GAMES_H
