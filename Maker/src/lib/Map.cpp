#include "Map.hpp"
#include <iostream>

using namespace std;

Map::Map(uint16_t w, uint16_t h) : width(w), height(h)
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
    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            cout << "(" << cells[(y*width)+x].tile << ", " << static_cast<int>(cells[(y*width)+x].flags) << ")";
        }
        cout << endl;
    }
    cout << endl;
}

void Map::write(Serializer::Writer &w) const
{
    w.write(cells);
    w.write(interactCells);
    w.write(pnjs);
    w.write(width);
    w.write(height);
}

/**
 * Modify cell's map
 */
void Map::modCell(CellMap cm, size_t index)
{
    if (cells.size() <= index)
        cells.resize((cells.size() + 1) * 2);
    this->cells[index] = cm;
}

/**
 * Modify interactCell's map
 */
void Map::modInteractCell(InteractCellMap im, size_t index)
{
    if (interactCells.size() <= index)
        interactCells.resize((interactCells.size() + 1) * 2);
    this->interactCells[index] = im;
}

/**
 * Modify pnj's map
 */
void Map::modPnj(Pnj p, size_t index)
{
    if (pnjs.size() <= index)
        pnjs.resize((pnjs.size() + 1) * 2);
    this->pnjs[index] = p;
}