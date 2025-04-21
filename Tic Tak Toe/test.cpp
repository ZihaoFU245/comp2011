#include <iostream>
#include <vector>
#include <limits> // Required for numeric_limits
#include <stdexcept> // Required for exception handling
#include <cassert> // For assertions
#include "games.h" // Include the main game header
#include "board.h" // Included indirectly via games.h, but good practice if needed directly
#include "player.h" // Included indirectly via games.h
#include "bots.h"   // Included indirectly via games.h

using namespace std;

// Helper function to print the board state from the vector
void print_board_vector(const vector<vector<char>>& board_state) {
    if (board_state.empty()) {
        cout << "Board is empty or invalid." << endl;
        return;
    }
    int size = board_state.size();

    // Helper lambda to print the horizontal separator line dynamically based on size
    auto printHorizontalLine = [size]() {
        for (int k = 0; k < size; ++k) {
            cout << "+---"; // Print "+---" for each column
        }
        cout << "+" << endl; // Print the final "+" and a newline
    };

    cout << "   "; // Initial spacing for column numbers
    for(int j = 0; j < size; ++j) {
        cout << " " << j << "  "; // Print column numbers
    }
    cout << endl;

    for (int i = 0; i < size; i++) {
        printHorizontalLine();
        cout << i << "| "; // Print row number and leading border
        for (int j = 0; j < size; j++) {
            cout << board_state[i][j] << " | "; // Print cell content
        }
        cout << endl;
    }
    printHorizontalLine(); // Print the final bottom border
}


int main() {
    try {
        // --- Game Setup ---
        string game_board_type = "15x15"; // Or "3x3"
        string game_match_type = "best_of_3"; // Or "best_of_5"
        string player_name = "Human";
        char player_symbol = 'X'; // Player chooses symbol

        // Determine bot symbol automatically
        char bot_symbol = (player_symbol == 'X') ? 'O' : 'X';

        cout << "--- Game Settings ---" << endl;
        cout << "Board: " << game_board_type << endl;
        cout << "Match: " << game_match_type << endl;
        cout << "Player: " << player_name << " (" << player_symbol << ")" << endl;
        cout << "Bot: Arno (" << bot_symbol << ")" << endl;
        cout << "---------------------" << endl;

        // Create the game instance
        Games game(game_board_type, game_match_type, player_name, player_symbol);

        // Optional: Assert bot symbol if Games class exposed it
        // assert(game.get_bot_symbol_internal() == bot_symbol && "Bot symbol mismatch!");

        cout << "Starting Game..." << endl;


        // --- Main Game Loop (Match) ---
        while (!game.is_match_over()) {

            // --- Round Start/Check ---
            if (game.is_round_over()) {
                cout << "\n--------------------" << endl;
                char round_winner = game.get_round_winner();
                cout << "Round Over! ";
                if (round_winner == 'D') {
                    cout << "It's a Draw!" << endl;
                } else {
                     cout << "Winner: " << round_winner << endl;
                }
                auto scores = game.get_scores();
                cout << "Current Score: Player(" << player_symbol << ") " << scores.first << " - " << scores.second << " Bot(" << bot_symbol << ")" << endl;
                cout << "Starting Next Round..." << endl;
                cout << "--------------------\n" << endl;
                game.start_new_round();
            }

            // --- Display Current State ---
            cout << "\n--- Current Board ---" << endl;
            print_board_vector(game.get_board_state());
            auto scores = game.get_scores();
            cout << "Score: Player(" << player_symbol << ") " << scores.first << " - " << scores.second << " Bot(" << bot_symbol << ")" << endl;
            cout << "Current Turn: Player " << game.get_current_player_symbol() << endl; // Ensure this line is active

            // --- Process Turn ---
            // Check if it's the bot's turn using the locally derived bot_symbol
            if (game.get_game_mode() == GameMode::PLAYER_VS_BOT && game.get_current_player_symbol() == bot_symbol) {
                cout << "Bot (" << bot_symbol << ")'s turn..." << endl;
                // Add a small delay to simulate thinking (optional)
                // #include <chrono>
                // #include <thread>
                // this_thread::sleep_for(chrono::milliseconds(500));

                if (!game.make_bot_move()) {
                     cout << "Bot could not make a move (Board full?)" << endl;
                     // This case should ideally be handled by draw detection before calling make_bot_move
                } else {
                    cout << "Bot placed its move." << endl;
                    // --- Display Board State (After Bot's Move) ---
                    cout << "\n--- Board After Bot's Move ---" << endl;
                    print_board_vector(game.get_board_state()); // Print board again immediately after bot moves
                }
            } else { // Human Player's turn
                unsigned short row, col;
                bool valid_move = false;
                while (!valid_move) {
                    cout << "Player (" << player_symbol << "), enter your move (row col): ";
                    cin >> row >> col;

                    // Basic input validation
                    if (cin.fail()) {
                        cout << "Invalid input. Please enter numbers." << endl;
                        cin.clear(); // Clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
                        continue; // Re-prompt
                    }

                    try {
                        // Attempt to make the move using the Games API
                        valid_move = game.make_player_move(row, col);
                        if (!valid_move) {
                            // The Games API should ideally only return false if the spot is taken/invalid
                            // Out-of-bounds might be better as an exception or checked beforehand.
                            cout << "Invalid move (spot taken or out of bounds?). Try again." << endl;
                        }
                    } catch (const std::logic_error& e) {
                        // Catch errors like trying to move when round/match is over, or not player's turn
                        cerr << "Logic Error: " << e.what() << endl;
                        // If the error indicates the game/round is over, the main loop condition should handle it.
                        // If it's not the player's turn, something is wrong with the test loop logic.
                        // For simplicity, we continue prompting, but a real GUI would handle state better.
                        valid_move = false; // Force re-prompt or let outer loop handle game over state
                    } catch (const std::out_of_range& e) {
                         // If make_player_move could throw out_of_range for bad coords
                         cerr << "Out of Range Error: " << e.what() << endl;
                         valid_move = false; // Re-prompt
                    }
                }
                 cout << "Player (" << player_symbol << ") placed move at (" << row << ", " << col << ")" << endl;
            }
        }

        // --- Match End ---
        cout << "\n====================" << endl;
        cout << "MATCH OVER!" << endl;
        auto final_scores = game.get_scores();
        cout << "Final Score: Player(" << player_symbol << ") " << final_scores.first << " - " << final_scores.second << " Bot(" << bot_symbol << ")" << endl;
        char match_winner = game.get_match_winner();
         if (match_winner == ' ') {
             cout << "Match Winner: Unknown or Draw (Should not happen in BoX?)" << endl;
         } else {
             cout << "Match Winner: Player " << match_winner << endl;
         }
        cout << "====================" << endl;

    } catch (const std::exception& e) {
        cerr << "\n>>> An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
