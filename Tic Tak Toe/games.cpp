#include "games.h"
#include <vector>
#include <stdexcept>
#include <iostream> // For potential debug messages

using namespace std;

// --- Private Helper Methods Implementation ---

void Games::switch_turn()
{
    if (mode == GameMode::PLAYER_VS_BOT)
    {
        current_player_symbol = (current_player_symbol == player_uno.get_symbol()) ? bot.get_symbol() : player_uno.get_symbol();
    }
    else
    { // PLAYER_VS_PLAYER
        current_player_symbol = (current_player_symbol == player_uno.get_symbol()) ? player_dos.get_symbol() : player_uno.get_symbol();
    }
}

// Checks if the player with 'player_symbol' has won the current round.
// Based on the logic previously in bots.cpp/check_win_at
bool Games::check_win_condition(char player_symbol)
{
    unsigned int size = board.get_size();

    // Directions: horizontal, vertical, diagonal down-right, diagonal down-left
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for (unsigned short r = 0; r < size; ++r)
    {
        for (unsigned short c = 0; c < size; ++c)
        {
            if (board.get_position(r, c) == player_symbol)
            {
                // Check all 4 directions from this cell
                for (int i = 0; i < 4; ++i)
                {
                    int count = 1;
                    // Check in the positive direction
                    for (int j = 1; j < win_combo; ++j)
                    {
                        unsigned short nr = r + dr[i] * j;
                        unsigned short nc = c + dc[i] * j;
                        if (nr < size && nc < size && board.get_position(nr, nc) == player_symbol)
                        {
                            count++;
                        }
                        else
                        {
                            break; // Sequence broken
                        }
                    }
                    // No need to check negative direction separately if we check from every cell

                    if (count >= win_combo)
                    {
                        return true; // Found a winning line
                    }
                }
            }
        }
    }
    return false; // No winning line found
}

bool Games::check_draw_condition()
{
    unsigned int size = board.get_size();
    for (unsigned int r = 0; r < size; ++r)
    {
        for (unsigned int c = 0; c < size; ++c)
        {
            if (board.get_position(r, c) == ' ')
            {
                return false; // Found an empty cell, not a draw yet
            }
        }
    }
    // No empty cells left, and assuming win condition was checked first
    return true;
}

void Games::update_state_after_move(bool move_made, char symbol)
{
    if (!move_made || match_over || current_round_state != GameState::ONGOING)
    {
        return; // No state change if move failed or game/round already over
    }

    if (check_win_condition(symbol))
    {
        current_round_state = GameState::WIN;
        round_winner_symbol = symbol;
        if (symbol == player_uno.get_symbol())
        {
            player_uno_wins++;
        }
        else
        {
            opponent_wins++;
        }

        if (player_uno_wins >= target_wins)
        {
            match_over = true;
            match_winner_symbol = player_uno.get_symbol();
        }
        else if (opponent_wins >= target_wins)
        {
            match_over = true;
            match_winner_symbol = (mode == GameMode::PLAYER_VS_BOT) ? bot.get_symbol() : player_dos.get_symbol();
        }
        // Don't switch turn if round/match ended with a win
    }
    else if (check_draw_condition())
    {
        current_round_state = GameState::DRAW;
        round_winner_symbol = 'D'; // Use 'D' or similar to indicate Draw
        // Don't switch turn if round ended with a draw
    }
    else
    {
        // Game continues, switch turn
        switch_turn();
    }
}

void Games::start_new_round_internal()
{
    if (match_over)
    {
        throw std::logic_error("Cannot start a new round, the match is already over.");
    }
    board.ResetBoard();
    current_round_state = GameState::ONGOING;
    round_winner_symbol = ' ';
    // Optional: Alternate who starts each round (e.g., based on round number or previous winner)
    // For simplicity, player 1 always starts for now.
    current_player_symbol = player_uno.get_symbol();
}

// --- Constructors Implementation ---

Games::Games(string game_type, string match_type, string player_name, char player_symbol)
    : player_uno(player_name, player_symbol),
      mode(GameMode::PLAYER_VS_BOT),
      player_uno_wins(0),
      opponent_wins(0),
      match_over(false),
      match_winner_symbol(' '),
      current_round_state(GameState::ONGOING),
      round_winner_symbol(' ')
{
    if (match_type == "best_of_3")
        target_wins = 2;
    else if (match_type == "best_of_5")
        target_wins = 3;
    else
        throw std::invalid_argument("Invalid match type. Use 'best_of_3' or 'best_of_5'.");

    unsigned short board_size;
    if (game_type == "3x3" || game_type == "mini")
    {
        board_size = 3;
        win_combo = 3;
    }
    else if (game_type == "15x15" || game_type == "formal")
    {
        board_size = 15;
        win_combo = 5;
    }
    else
    {
        throw std::invalid_argument("Invalid game type. Use '3x3', 'mini', '15x15', or 'formal'.");
    }

    board = Boards(board_size);
    bot = Bots((player_symbol == 'X' ? 'O' : 'X'), win_combo); // Bot gets opposite symbol
    current_player_symbol = player_uno.get_symbol();           // Player 1 starts
    start_new_round_internal();                                // Initialize first round state
}

Games::Games(string game_type, string match_type, string p1_name, char p1_sym, string p2_name, char p2_sym)
    : player_uno(p1_name, p1_sym),
      player_dos(p2_name, p2_sym), // Initialize player 2
      mode(GameMode::PLAYER_VS_PLAYER),
      player_uno_wins(0),
      opponent_wins(0),
      match_over(false),
      match_winner_symbol(' '),
      current_round_state(GameState::ONGOING),
      round_winner_symbol(' ')
{
    if (p1_sym == p2_sym)
    {
        throw std::invalid_argument("Player 1 and Player 2 cannot have the same symbol.");
    }
    if (match_type == "best_of_3")
        target_wins = 2;
    else if (match_type == "best_of_5")
        target_wins = 3;
    else
        throw std::invalid_argument("Invalid match type. Use 'best_of_3' or 'best_of_5'.");

    unsigned short board_size;
    if (game_type == "3x3" || game_type == "mini")
    {
        board_size = 3;
        win_combo = 3;
    }
    else if (game_type == "15x15" || game_type == "formal")
    {
        board_size = 15;
        win_combo = 5;
    }
    else
    {
        throw std::invalid_argument("Invalid game type. Use '3x3', 'mini', '15x15', or 'formal'.");
    }

    board = Boards(board_size);
    // Bot is default constructed but not used
    current_player_symbol = player_uno.get_symbol(); // Player 1 starts
    start_new_round_internal();                      // Initialize first round state
}

// --- Public API Methods Implementation ---

bool Games::make_player_move(unsigned short row, unsigned short col)
{
    if (match_over)
        throw std::logic_error("Match is over.");
    if (current_round_state != GameState::ONGOING)
        throw std::logic_error("Current round is over.");

    Players *current_human_player = nullptr;
    if (current_player_symbol == player_uno.get_symbol())
    {
        current_human_player = &player_uno;
    }
    else if (mode == GameMode::PLAYER_VS_PLAYER && current_player_symbol == player_dos.get_symbol())
    {
        current_human_player = &player_dos;
    }
    else
    {
        throw std::logic_error("Not the specified player's turn or trying to move bot.");
    }

    bool move_made = current_human_player->move(board, row, col);
    update_state_after_move(move_made, current_human_player->get_symbol());
    return move_made;
}

bool Games::make_bot_move()
{
    if (mode != GameMode::PLAYER_VS_BOT)
        throw std::logic_error("Not a Player vs Bot game.");
    if (match_over)
        throw std::logic_error("Match is over.");
    if (current_round_state != GameState::ONGOING)
        throw std::logic_error("Current round is over.");
    if (current_player_symbol != bot.get_symbol())
        throw std::logic_error("Not the bot's turn.");

    // Bot's move logic inherently checks for valid spots.
    // We assume bot.move() will eventually place a piece if possible.
    bot.move(board); // Bot modifies the board directly
    // We need to know if the bot *actually* made a move (i.e., board wasn't full)
    // For now, assume bot.move always succeeds if called when board isn't full.
    // A better bot.move might return bool or the chosen coords.
    // Let's assume it succeeded if the game wasn't already a draw.
    bool move_succeeded = !check_draw_condition(); // Approximation
    update_state_after_move(move_succeeded, bot.get_symbol());
    return move_succeeded; // Return if a move was likely made
}

void Games::start_new_round()
{
    if (match_over)
    {
        // Or just return silently, depends on desired API behavior
        throw std::logic_error("Cannot start a new round, the match is already over.");
    }
    if (current_round_state == GameState::ONGOING)
    {
        // Or just return silently
        throw std::logic_error("Cannot start a new round while the current round is ongoing.");
    }
    start_new_round_internal();
}

vector<vector<char>> Games::get_board_state() const
{
    unsigned int size = board.get_size();
    vector<vector<char>> board_copy(size, vector<char>(size));
    for (unsigned int r = 0; r < size; ++r)
    {
        for (unsigned int c = 0; c < size; ++c)
        {
            board_copy[r][c] = board.get_position(r, c);
        }
    }
    return board_copy;
}
