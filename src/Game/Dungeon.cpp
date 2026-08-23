#include "Dungeon.hpp"
#include "Map.hpp"

Dungeon::Dungeon()
{
    floors.push_back(new Map("test_map001.map"));
}

void Dungeon::process(long double delta, uint64_t tick)
{
    floors[floor]->process(delta, tick);
}

void Dungeon::render(long double delta, uint64_t tick)
{
    floors[floor]->render(delta, tick);
}