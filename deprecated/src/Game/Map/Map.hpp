#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "Player.hpp"
#include "Item.hpp"

enum Tile
{
    Grass,
    Stone,
    WoodBridge,
    Void,
    Air,
};

typedef struct
{
    uint8_t flags;
    Tile type;
} Cell;

typedef struct
{
    float x, y;
} Coordinate;

class Serializer;

class Map
{

public:
    Map(std::string filename);
    Map(unsigned int _width, unsigned int _height, std::vector<Entity *> things);

    ~Map();
    Cell *operator()(size_t x, size_t y)
    {
        return &map[y * width + x];
    }

    inline Coordinate asytoPixel(Coordinate p)
    {
        return {
            (p.x - p.y) * tile_width / 2,
            (p.x + p.y) * (tile_height / 4)};
    }

    inline Coordinate pixelToAsy(Coordinate p)
    {
        return {
            (p.x / (tile_width / 2) + p.y / (tile_height / 2)) / 2,
            (p.y / (tile_height / 2) - p.x / (tile_width / 2)) / 2};
    }

    void enter(Player *p);
    void exit();

    void process(long double delta, uint64_t tick);
    void render(long double delta, uint64_t tick);

    void debug_print();

    void load(Serializer &s);
    void save(Serializer &s);

    unsigned int width, height;
    std::vector<Cell> map;
    std::vector<Entity *> things;
    Player *p;

    float tile_width = 150, tile_height = 150, start_draw_x, start_draw_y;

    int SPEED = 100;

    bool create_from_file = false;
    bool is_active;
};

#endif