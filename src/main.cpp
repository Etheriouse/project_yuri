#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "GameWindow.hpp"
#include "Map/Map.hpp"
#include "Game/Player.hpp"

int main(int argc, char const *argv[])
{

    Window *_window = new Window();
    Player *p = new Player("knight", 10, 5);
    std::vector<Entity *> things;
    std::vector<Item *> thongs;
    Map *encounter = new Map(6, 6, p, things, thongs);

    std::cout << p->hp << std::endl;

    delete _window;
    delete encounter;
    return 0;
}
