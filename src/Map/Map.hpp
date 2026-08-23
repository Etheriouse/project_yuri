#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include "../Game/Player.hpp"
#include "../Game/Item.hpp"

enum Tile {
    Floor,
    Wall,
};

typedef struct
{
    uint8_t flags;
    Tile type;
} Cell;

class Serializer;

class Map
{

public:

    /**
     * Given ptr natural is not responsability of map object
     * so vector of ptr is responsability of map object
     */
    Map(std::string filename, Player *p);

    
    /**
     * Given ptr natural is not responsability of map object
     * so vector of ptr is responsability of map object, entity* had to be new object
     */
    Map(unsigned int _width, unsigned int _height, Player *p, std::vector<Entity*> things);
    
    /** destroy vector of entity* */
    ~Map();

    inline Cell *get(unsigned int x, unsigned int y);

    void run();
    void exit();

    void process(long double delta, uint64_t tick);
    void render(long double delta, uint64_t tick);

    void debug_print();

    void load(Serializer &s);
    void save(Serializer &s);

    unsigned int width, height;
    std::vector<Cell> map;
    std::vector<Entity*> things;
    Player *p;

    bool is_active;
};

#endif