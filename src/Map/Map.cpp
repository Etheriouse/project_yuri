#include "Map.hpp"

#include <stdlib.h>

Map::Map(unsigned int _width, unsigned int _height, Player *p, std::vector<Entity *> things, std::vector<Item *> thongs)
    : width(_width), height(_height), map(width * height), things(things), thongs(thongs), p(p)
{
    // place the things and the thongs little randomly into the cell map
}

Map::~Map()
{
}

Cell *Map::get(unsigned int x, unsigned int y)
{
    return &this->map[y * width + x];
}
