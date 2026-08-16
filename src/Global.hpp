#ifndef GAME_GLOBAL_HPP
#define GAME_GLOBAL_HPP

#include "Game.hpp"


extern Game g_game;
void set_game(std::string filename);
void save_game(std::string filename);

#endif