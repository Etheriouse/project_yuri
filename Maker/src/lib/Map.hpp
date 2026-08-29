#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

#include "Pnj.hpp"

class Player;

enum TileMap
{
    Grass
};

enum InteractTileMap
{
    Button
};

typedef struct
{
    uint8_t flags;
    TileMap tile;

    void save(std::ofstream &file)
    {
        file.write(reinterpret_cast<const char *>(&flags), sizeof(flags));
        file.write(reinterpret_cast<const char *>(&tile), sizeof(tile));
    }
} CellMap;

typedef struct
{
    uint16_t x, y;
    uint8_t flags;
    InteractTileMap tile;

    void save(std::ofstream &file)
    {
        file.write(reinterpret_cast<const char *>(&x), sizeof(x));
        file.write(reinterpret_cast<const char *>(&y), sizeof(y));
        file.write(reinterpret_cast<const char *>(&flags), sizeof(flags));
        file.write(reinterpret_cast<const char *>(&tile), sizeof(tile));
    }
} InteractCellMap;

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

    void debugPrint();

    void write(std::string filename);

    // classic cell
    std::vector<CellMap> cells;
    // interactible cell
    std::vector<InteractCellMap> interactCells;
    // pnj
    std::vector<Pnj> pnjs;

    uint16_t width, height;
private:

    /** Reference to the player of Game */
    Player *player;
};

void mapSerialize(Map m);

#endif