#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "MapMaker.hpp"
#include "Map.hpp"

using namespace std;

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
            data.push_back(std::stoi(value) + 1);
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
        TileMap tile = static_cast<TileMap>(v);
        CellMap c = {0, tile};
        m.modCell(c, i);
        i++;
    }

    m.debugPrint();

    // parcour the csv and all layer to make

    // use the settings map to chose each

    printf("Hello make map %s\n", filename);
}
