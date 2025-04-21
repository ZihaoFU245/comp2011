#ifndef GAMES_H
#define GAMES_H

// Tic Tac Toe game
#include "utils.h"
#include "player.h"
#include "board.h"
#include "bots.h"
#include <string>
using namespace std;

class Games
{
private:
    Boards board;
    Players player_uno;
    Players player_dos;
    Bots bot;
    unsigned int player_points;
    unsigned int bot_points;


public:
    Games(); // Default constructor , for 3x3 game vs Bot
    Games(string game_type, string player_name, char symbol); // Constructor for single player vs Bot
    Games(string game_type, string p1_name, char p1_sym, string p2_name, char p2_sym); // Constructor for two players

    // Add game logic methods later (e.g., play(), check_win(), etc.)
    void start_game();
    bool check_win();
    

};

#endif //GAMES_H
