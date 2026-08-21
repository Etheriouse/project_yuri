#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "GameWindow.hpp"
#include "Map/Map.hpp"
#include "Game/Player.hpp"
#include "Game/Mob.hpp"

#include "Global.hpp"
#include "Serializer/Serializer.hpp"


// a tester les save load unload de worldmap
// a faire le constructeur de fichier worldmap a partir d'image layer


// maybe faire des dungon qui sont un ensemble de map et qui est placer sur la carte

// maybe commencer a faire la parti render lol
// et la parti move sur la world map (px par px)
// et la parti move sur la map (case par case)

int main(int argc, char const *argv[])
{
    
    std::string filename_save = "game.rrl"; // random rogue lite
    set_game(filename_save);
    g_game.debug_print();

    // run game

    g_game.run();

    save_game(filename_save);
    return 0;
}
