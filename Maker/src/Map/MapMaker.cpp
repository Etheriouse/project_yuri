#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "MapMaker.hpp"
#include "Map.hpp"

#include "json.hpp"

using namespace std;

const map<int, CellMap> translateCellId = {
    {0, {0, TileMap::Grass}},
    {1, {0, TileMap::Stone}},
    {2, {0, TileMap::Lava}},
    {3, {0, TileMap::Water}}
};

CellMap translateCell(int id) {
    auto it = translateCellId.find(id);
    if(it == translateCellId.end()) return {0, TileMap::Default};
    return it->second;
}

void makeMap(const char *filename, const char *settings)
{
    std::ifstream file(filename);
    std::string line;
    uint16_t width, height = 0;

    vector<int> data;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string value;
        width = 0;
        while (std::getline(ss, value, ','))
        {
            data.push_back(std::stoi(value));
            width++;
        }
        height++;
    }

    Map m(width, height);

    cout << data.size() << endl;

    cout << width << ", " << height << endl;

    size_t i = 0;
    for (auto v : data)
    {
        m.modCell(translateCell(v), i);
        i++;
    }

    m.iDebugPrint();

    printf("Hello make map %s\n", filename);

    Serializer::Writer s("base.map");
    m.write(s);
}
