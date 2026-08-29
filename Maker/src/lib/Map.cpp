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


// do a map serializer for global? 

// define save file for this to know if this is usefull

void Map::debugPrint()
{
}

void write_(CellMap element, ofstream &file)
{
    element.save(file);
}

void write_(InteractCellMap element, ofstream &file)
{
    element.save(file);
}

void write_(Pnj p, ofstream &file)
{
    p.save(file);
}

template <typename T>
void writeV(std::vector<T> v, ofstream &file)
{
    size_t cellCount = v.size();
    file.write(
        reinterpret_cast<const char *>(&cellCount),
        sizeof(cellCount));
    for (auto element : v)
    {
        write_(element, file);
    }
}

void Map::write(std::string filename)
{
    ofstream file("save.bin", ios::binary);
    writeV(cells, file);
    writeV(interactCells, file);
    writeV(pnjs, file);
    file.write(reinterpret_cast<const char*>(width), sizeof(width));
    file.write(reinterpret_cast<const char*>(height), sizeof(height));
}

void mapSerialize(Map m)
{
}