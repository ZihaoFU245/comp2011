#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Needed for vector, pair, string conversions
#include <pybind11/operators.h> // If you need operator bindings (not used here yet)
#include <stdexcept> // For exception translation

#include "games.h" // Your main game logic header

namespace py = pybind11;

// Helper function to translate C++ exceptions to Python exceptions
void translate_exception(const std::exception &e) {
    // You can customize this mapping
    if (dynamic_cast<const std::invalid_argument*>(&e)) {
        PyErr_SetString(PyExc_ValueError, e.what());
    } else if (dynamic_cast<const std::logic_error*>(&e)) {
        PyErr_SetString(PyExc_RuntimeError, e.what()); // Or a more specific Python error
    } else if (dynamic_cast<const std::out_of_range*>(&e)) {
         PyErr_SetString(PyExc_IndexError, e.what());
    }
     else {
        PyErr_SetString(PyExc_Exception, e.what()); // Generic fallback
    }
}


PYBIND11_MODULE(TicTakToe, m) { // Module name is TicTakToe
    m.doc() = "pybind11 plugin for Tic Tac Toe / Gomoku game logic"; // Optional module docstring

    // Register the exception translator
    py::register_exception_translator([](std::exception_ptr p) {
        try {
            if (p) std::rethrow_exception(p);
        } catch (const std::exception &e) {
            translate_exception(e);
        }
    });

    // Bind the GameMode enum
    py::enum_<GameMode>(m, "GameMode")
        .value("PLAYER_VS_PLAYER", GameMode::PLAYER_VS_PLAYER)
        .value("PLAYER_VS_BOT", GameMode::PLAYER_VS_BOT)
        .export_values(); // Make enum values accessible directly (e.g., TicTakToe.GameMode.PLAYER_VS_BOT)

    // Bind the Games class
    py::class_<Games>(m, "Game") // Use "Game" as the Python class name
        // Constructor for Player vs Bot
        .def(py::init<string, string, string, char>(),
             py::arg("game_type"), py::arg("match_type"), py::arg("player_name"), py::arg("player_symbol"))
        // Constructor for Player vs Player
        .def(py::init<string, string, string, char, string, char>(),
             py::arg("game_type"), py::arg("match_type"), py::arg("p1_name"), py::arg("p1_sym"), py::arg("p2_name"), py::arg("p2_sym"))

        // --- Bind Methods ---
        .def("make_player_move", &Games::make_player_move,
             py::arg("row"), py::arg("col"), "Attempts to place the current player's symbol. Returns true if successful.")
        .def("make_bot_move", &Games::make_bot_move, "Makes the bot's move. Returns true if successful.")
        .def("start_new_round", &Games::start_new_round, "Resets the board for a new round.")

        // --- Bind State Query Methods ---
        .def("get_board_state", &Games::get_board_state, "Returns the current board state as a list of lists.")
        .def("get_current_player_symbol", &Games::get_current_player_symbol, "Returns the symbol of the player whose turn it is.")
        .def("is_round_over", &Games::is_round_over, "Returns true if the current round has ended (win or draw).")
        .def("get_round_winner", &Games::get_round_winner, "Returns the winner's symbol ('D' for draw, ' ' for ongoing).")
        .def("is_match_over", &Games::is_match_over, "Returns true if the best-of-X match has concluded.")
        .def("get_match_winner", &Games::get_match_winner, "Returns the overall match winner's symbol (' ' if not over).")
        .def("get_scores", &Games::get_scores, "Returns the current match scores as a tuple (player1_wins, opponent_wins).")
        .def("get_game_mode", &Games::get_game_mode, "Returns the current game mode (PvP or PvB).")
        .def("get_win_combo", &Games::get_win_combo, "Returns the number of symbols needed in a row to win.");

    // You might need to bind other classes like Boards, Players, Bots if you want to expose them directly,
    // but for a simple API, binding just the 'Games' class is often sufficient.
}
