#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
    if (place != nullptr)
        delete place;
    if (dungeon != nullptr)
        delete dungeon;
}

void Game::render(long double delta, uint64_t tick)
{
    if (placeOrDungeon)
    {
        if (place == nullptr)
            return;
        place->render(delta, tick);
    }
    else
    {
        if (dungeon == nullptr)
            return;
        dungeon->render(delta, tick);
    }
}

void Game::process(long double delta, uint64_t tick)
{
    if (placeOrDungeon)
    {
        if (place == nullptr)
            return;
        place->process(delta, tick);
    }
    else
    {
        if (dungeon == nullptr)
            return;
        dungeon->process(delta, tick);
    }
}
