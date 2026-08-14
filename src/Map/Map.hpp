#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "../Game/Player.hpp"
#include "../Game/Item.hpp"

typedef struct
{
    void *texture;
    std::vector<Entity *> entitys;
    std::vector<Item *> items;
} Cell;

class Map
{

public:
    Map(unsigned int _width, unsigned int _height, Player *p, std::vector<Entity *> things, std::vector<Item *> thongs);
    ~Map();

    Cell *get(unsigned int x, unsigned int y);

    unsigned int width, height;
    Player *p;
    std::vector<Entity *> things;
    std::vector<Item *> thongs;
    std::vector<Cell> map;
};

#endif