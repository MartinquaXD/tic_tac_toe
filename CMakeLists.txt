cmake_minimum_required(VERSION 3.15)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 20)

add_executable(tic_tac_toe main.cpp src/game.cpp src/game.hpp src/console.cpp src/console.hpp src/types.hpp)