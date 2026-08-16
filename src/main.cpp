#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "GameWindow.hpp"
#include "Map/Map.hpp"
#include "Game/Player.hpp"
#include "Serializer/Serializer.hpp"

int main(int argc, char const *argv[])
{
    std::string filename_save = "game.rrl";
    // Serializer *s = new Serializer(filename_save, SAVE_MODE);
   // Serializer *s = new Serializer(filename_save, LOAD_MODE);
    Game *g = new Game();
    // g->save(*s);
    // g->load(*s);
    g->debug_print();
    // delete s;
    return 0;
}
