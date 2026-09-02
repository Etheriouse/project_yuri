#include "Map.hpp"

using namespace std;

Map::Map()
{
}

Map::Map(string filename, Player *p) : player(p)
{
}

Map::~Map()
{
}

void Map::render(long double delta, uint64_t tick)
{
}

void Map::process(long double delta, uint64_t tick)
{
}

void Map::debugPrint()
{
}

void Map::write(Serializer::Writer &w) const {
    w.write(cells);
    w.write(interactCells);
    w.write(pnjs);
    w.write(width);
    w.write(height);
}

