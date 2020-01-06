//
// Created by martinbeckmann on 06.01.20.
//

#ifndef UNTITLED_CONSOLE_HPP
#define UNTITLED_CONSOLE_HPP

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <optional>
#include "types.hpp"


class Console {
private:
    struct termios terminal;

    void disable_raw_mode();
    void enable_raw_mode();

    static void render_line(unsigned int length);
    static void render_board_row(const GameState& game_state, unsigned int start, unsigned int end);
    static void render_instructions();
    static void render_player_message(std::optional<Player> winner, bool is_draw, Player turn);
    static void render_texts(Player player, std::optional<Player> winner, bool is_draw);
    static void clear_screen();
    static void render_board(const GameState& state);

public:
    static void render_screen(const GameState& state, Player player, std::optional<Player> winner, bool is_draw);
    Console();
    ~Console();

};


#endif //UNTITLED_CONSOLE_HPP
