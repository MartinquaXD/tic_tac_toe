//
// Created by martinbeckmann on 06.01.20.
//

#ifndef UNTITLED_GAME_HPP
#define UNTITLED_GAME_HPP

#include "console.hpp"
#include "types.hpp"
#include <optional>

class Game {
private:
    GameState tiles;
    Player player = Player::X;
    Console console;
    bool is_running = true;
    bool is_draw = false;
    std::optional<Player> winner{};
    u_int8_t round = 0;

    void place_tile(u_int8_t tile_index);

    void render() const;

    void handle_raw_input();

    void reset_game();

    std::optional<Player> check_row_for_winner(u_int8_t row_index) const;

    std::optional<Player> check_rows_for_winner() const;

    std::optional<Player> check_column_for_winner(u_int8_t col_index) const;

    std::optional<Player> check_columns_for_winner() const;

    std::optional<Player> check_diagonals_for_winner() const;

    std::optional<Player> check_for_winner() const;

    void update_winner();


public:
    Game();
    void run();
};


#endif //UNTITLED_GAME_HPP
