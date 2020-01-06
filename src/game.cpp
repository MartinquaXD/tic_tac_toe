//
// Created by martinbeckmann on 06.01.20.
//

#include "game.hpp"
#include <algorithm>

void Game::place_tile(u_int8_t tile_index) {
    tiles.at(tile_index) = player;
    player = player == Player::X ? Player::O : Player::X;
    ++round;
}

void Game::render() const {
    Console::render_screen(tiles, player, winner, is_draw);
}

void Game::handle_raw_input() {
    char c;
    read(STDIN_FILENO, &c, 1);

    if (c == 'q') {
        is_running = false;
    } else if (c == 'r') {
        reset_game();
    } else if (!winner.has_value() && '1' <= c && c <= '9') {
        auto board_index = c - '1';
        if (!tiles.at(board_index).has_value()) {
            place_tile(board_index);
        }
    }
}

void Game::run() {
    render();
    while (is_running) {
        handle_raw_input();
        update_winner();
        if(round >= 9 && !winner.has_value()){
            is_draw = true;
        }
        render();
    }
}

std::optional<Player> Game::check_row_for_winner(u_int8_t row_index) const {
    auto start = tiles.begin() + row_index * 3;
    auto end = start + 3;
    if (std::adjacent_find(start, end, std::not_equal_to<>()) == end) {
        return *start;
    }
    return {};
}

std::optional<Player> Game::check_column_for_winner(u_int8_t col_index) const {
    const auto start = tiles.begin() + col_index;
    if(*start == *(start + 3) && *start == *(start + 6)){
        return *start;
    }
    return {};
}

std::optional<Player> Game::check_for_winner() const {
    if (const auto winner = check_rows_for_winner(); winner.has_value()) {
        return winner;
    }

    if (const auto winner = check_columns_for_winner(); winner.has_value()) {
        return winner;
    }

    if (const auto winner = check_diagonals_for_winner(); winner.has_value()) {
        return winner;
    }

    return {};
}

std::optional<Player> Game::check_rows_for_winner() const {
    for (auto i = 0; i < 3; ++i) {
        if (const auto winner = check_row_for_winner(i); winner.has_value()) {
            return winner;
        }
    }
    return {};
}

void Game::reset_game() {
    winner = {};
    is_draw = false;
    tiles.fill({});
    player = Player::X;
    round = 0;
}

void Game::update_winner() {
    const auto new_winner = check_for_winner();
    if (!winner.has_value() && new_winner.has_value()) {
        winner = new_winner;
    }
}

Game::Game() : tiles(), player(Player::X), console(), is_running(true), is_draw(false), winner() {
    tiles.fill({});
}

std::optional<Player> Game::check_columns_for_winner() const {
    for(int i = 0; i < 3; ++i) {
        if (const auto winner = check_column_for_winner(i); winner.has_value()) {
            return winner;
        }
    }

    return {};
}

std::optional<Player> Game::check_diagonals_for_winner() const {
    const auto top_left = tiles.at(0);
    if(top_left.has_value() && top_left == tiles.at(4) && top_left == tiles.at(8)){
        return *top_left;
    }

    const auto top_right = tiles.at(2);
    if(top_right.has_value() && top_right == tiles.at(4) && top_right == tiles.at(6)){
        return *top_right;
    }

    return {};
}


