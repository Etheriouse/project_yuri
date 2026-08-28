#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include <cstdint>
#include <string>

class Player;

enum TileMap
{

};

typedef struct
{
    uint8_t flags;
    TileMap tile;
} CellMap;

class Map
{

public:
    Map();
    
    Map(std::string filename, Player *p);
    ~Map();


    /**
     * render the game or the actual things used at the screen
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void render(long double delta, uint64_t tick);

    /**
     * Process the game if a game is in court
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void process(long double delta, uint64_t tick);

private:
    std::vector<CellMap> cells;

    /** Reference to the player of Game */
    Player *player;


};

void mapSerialize(Map m);

#endif