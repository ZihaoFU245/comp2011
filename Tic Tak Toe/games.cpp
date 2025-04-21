#include "games.h"
#include <stdexcept>
#include <iostream> // For potential error messages or debugging
using namespace std;

// Default constructor: 3x3 game, Player 'O', Bot 'X'
Games::Games()
    : board(3),                                             // Default 3x3 board
      player_uno("Player 1", 'O'),                          // Default player
      bot((player_uno.get_symbol() == 'X' ? 'O' : 'X'), 3), // Bot gets opposite symbol, 3-in-a-row
      player_points(0),
      bot_points(0)
{}

// Constructor for specific game type (single player vs bot)
Games::Games(string game_type, string player_name, char symbol)
    : player_uno(player_name, symbol), // Initialize player first to get symbol
      player_points(0),
      bot_points(0)
// Board and Bot initialization depends on game_type
{
    unsigned short board_size;
    unsigned short win_combo;

    if (game_type == "3x3" || game_type == "mini")
    {
        board_size = 3;
        win_combo = 3;
    }
    else if (game_type == "15x15" || game_type == "formal")
    {
        board_size = 15;
        win_combo = 5; // Standard Gomoku win condition
    }
    else
    {
        // Handle invalid type - Option 1: Default to 3x3
        // cout << "Invalid game type specified, defaulting to 3x3." << endl;
        // board_size = 3;
        // win_combo = 3;

        // Handle invalid type - Option 2: Throw an exception
        throw std::invalid_argument("Invalid game type specified. Use '3x3', 'mini', '15x15', or 'formal'.");
    }

    // Now initialize board and bot using determined values
    board = Boards(board_size);                         // Use assignment or re-initialize if needed, direct init preferred
    bot = Bots((symbol == 'X' ? 'O' : 'X'), win_combo); // Bot gets opposite symbol and correct win condition

    // If direct initialization in the list is preferred and possible (requires helper or C++17):
    // This structure is generally preferred if feasible.
    /*
    : board(determine_board_size(game_type)), // Requires helper or logic before initializer list
      player_uno(player_name, symbol),
      bot(determine_bot_symbol(symbol), determine_win_combo(game_type)), // Requires helpers
      player_points(0),
      bot_points(0)
    */
}

// two player constructor
Games::Games(string game_type, string p1_name, char p1_sym, string p2_name, char p2_sym)
    : player_uno(p1_name, p1_sym),
      player_dos(p2_name, p2_sym),
      player_points(0), // Points for player_uno
      bot_points(0)     // Re-purpose/rename later if needed for player_dos points
      // bot member is default constructed but not used in this mode
{
    // Ensure players have different symbols
    if (p1_sym == p2_sym) {
        throw std::invalid_argument("Player 1 and Player 2 cannot have the same symbol.");
    }

    unsigned short board_size;
    // Win combo is determined by game logic, not needed for bot here
    // unsigned short win_combo; // Not directly needed for bot setup here

    if (game_type == "3x3" || game_type == "mini")
    {
        board_size = 3;
        // win_combo = 3;
    }
    else if (game_type == "15x15" || game_type == "formal")
    {
        board_size = 15;
        // win_combo = 5;
    }
    else
    {
        throw std::invalid_argument("Invalid game type specified. Use '3x3', 'mini', '15x15', or 'formal'.");
    }

    // Initialize board
    board = Boards(board_size);

    // Note: The 'bot' member is still present and default-initialized.
    // Consider refactoring if 'bot' and 'bot_points' are strictly for AI games.
    // Maybe use a union, std::variant, or separate classes for different game modes.
    // For now, bot_points will represent player_dos's score conceptually.
    // You might want to add a specific member for player_dos_points.
}

// Methods

