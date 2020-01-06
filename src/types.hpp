//
// Created by martinbeckmann on 06.01.20.
//

#ifndef UNTITLED_TYPES_HPP
#define UNTITLED_TYPES_HPP

#include <array>
#include <iostream>
#include <optional>

enum class Player {
    X, O
};

typedef std::array<std::optional<Player>, 9> GameState;

#endif //UNTITLED_TYPES_HPP
