//
// Created by martinbeckmann on 06.01.20.
//

#include "console.hpp"
#include <string>
#include <iostream>

void Console::disable_raw_mode() {
    tcgetattr(STDIN_FILENO, &terminal);
    terminal.c_lflag &= ECHO | ICANON;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
}

void Console::enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &terminal);
    terminal.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminal);
}

Console::~Console() {
    disable_raw_mode();
}

Console::Console(): terminal{} {
    enable_raw_mode();
}

void Console::clear_screen() {
    std::cout << "\x1b[2J\x1b[H";
}

void Console::render_board(const GameState & state) {
    render_line(7);
    render_board_row(state, 0, 2);
    render_board_row(state, 3, 5);
    render_board_row(state, 6, 8);
    render_line(7);
}

void Console::render_line(unsigned int length) {
    for (int i = 0; i < length; ++i) {
        std::cout << "_";
    }
    std::cout << "\n";
}

void Console::render_board_row(const GameState &game_state, unsigned int start, unsigned int end) {
    for (auto i = start; i <= end; ++i) {
        std::cout << "|";
        const auto symbol = [&game_state, i] {
            const auto tile = game_state.at(i);
            if (!tile.has_value()) {
                return static_cast<char>('0' + i + 1);
            } else if (*tile == Player::X) {
                return 'X';
            } else {
                return 'O';
            }
        }();
        std::cout << symbol;
    }
    std::cout << "|\n";
}

char symbol_for_player(const Player player) {
    switch (player) {
        case Player::X:
            return 'X';
        case Player::O:
            return 'O';
        default:
            return '?';
    }
}

void Console::render_instructions() {
    std::cout << "Press q to quit\n"
        << "Press r to reset game" << std::endl;
}

void Console::render_player_message(std::optional<Player> winner, bool is_draw, Player turn) {
    if(winner.has_value()) {
        std::cout << "\nPlayer " << symbol_for_player(*winner) << " won the game! :D" << std::endl;
    } else if (is_draw) {
        std::cout << "\nYou 2 reached a draw!" << std::endl;
    } else {
        std::cout << "\nPlayer " << symbol_for_player(turn) << " press the number where your tile should be placed on the board.\n";
    }
}

void Console::render_texts(Player player, std::optional<Player> winner, bool is_draw) {
    render_player_message(winner, is_draw, player);
    render_instructions();
}

void Console::render_screen(const GameState &state, Player player, std::optional<Player> winner, bool is_draw) {
    render_board(state);
    render_texts(player, winner, is_draw);
}
