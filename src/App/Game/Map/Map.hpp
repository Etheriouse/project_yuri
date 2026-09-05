#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

#include "Serializer.hpp"
#include "Pnj.hpp"
#include "Global.hpp"

class Player;

enum TileMap
{
    Default,
    Grass,
    Stone,
    Lava,
    Water
};

enum InteractTileMap
{
    Button
};

typedef struct
{
    uint8_t flags;
    TileMap tile;

    void write(Serializer::Writer &w) const
    {
        w.write(flags);
        w.write(tile);
    }

    void read(Serializer::Reader &r)
    {
        r.read(flags);
        r.read(tile);
    }
} CellMap;

typedef struct
{
    uint16_t x, y;
    uint8_t flags;
    InteractTileMap tile;

    void write(Serializer::Writer &w) const
    {
        w.write(x);
        w.write(y);
        w.write(flags);
        w.write(tile);
    }

    void read(Serializer::Reader &r)
    {
        r.read(x);
        r.read(y);
        r.read(flags);
        r.read(tile);
    }
} InteractCellMap;

class Map
{

public:
    Map() : width(0), height(0) {};
    Map(uint16_t w, uint16_t h);

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

    // Create map from file function

    /**
     * Modify cell's map
     */
    void modCell(CellMap cm, size_t index);

    /**
     * Modify interactCell's map
     */
    void modInteractCell(InteractCellMap im, size_t index);

    /**
     * Modify pnj's map
     */
    void modPnj(Pnj p, size_t index);

    /**
     * Print in the console a representation of the map
     */
    void debugPrint();

    /**
     * Print in the console a illustration of the map
     */
    void iDebugPrint();

    /**
     * Serializer function for map
     * @param w a writer serializer
     */
    void write(Serializer::Writer &w) const;

private:
    // classic cell
    std::vector<CellMap> cells;
    // interactible cell
    std::vector<InteractCellMap> interactCells;
    // pnj
    std::vector<Pnj> pnjs;

    uint16_t width, height;

    /** Reference to the player of Game */
    Player *player;

    Size tileSize = {16, 16};
    Size start = {0, 0};
};

#endif