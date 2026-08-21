#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "../Game/Player.hpp"
#include "../Game/Item.hpp"

enum TypeTile {
    Floor,
    Wall,
};

typedef struct
{
    std::string texture;
    TypeTile type;
} Cell;

typedef struct 
{
    unsigned int x, y;
    Entity *entity;
} MapEntity;

class Serializer;

class Map
{

public:

    Map(std::string filename, Player *p);
    Map(unsigned int _width, unsigned int _height, Player *p, std::vector<MapEntity> things);
    ~Map();

    inline Cell *get(unsigned int x, unsigned int y);

    void run();
    void exit();

    void process(long double delta, uint64_t tick);
    void render(long double delta, uint64_t tick);

    void debug_print();

    void save(Serializer &s);

    unsigned int width, height;
    std::vector<Cell> map;
    std::vector<MapEntity> things;
    Player *p;
    bool is_active;
};

#endif