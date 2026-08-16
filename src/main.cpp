#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "GameWindow.hpp"
#include "Map/Map.hpp"
#include "Game/Player.hpp"

#include "Global.hpp"

int main(int argc, char const *argv[])
{
    std::string filename_save = "game.rrl";
    set_game(filename_save);
    g_game.debug_print();

    // run game

    save_game(filename_save);
    return 0;
}
