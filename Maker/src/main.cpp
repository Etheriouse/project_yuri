#include <string>
#include <iostream>

#include "MapMaker.hpp"
#include "DungeonMaker.hpp"

int main(int argc, char const *argv[])
{
    if(argc != 4) return -1;

    if(argv[1] == std::string("map")) makeMap(argv[2], argv[3]);
    else if(argv[1] == std::string("dungeon")) makeDungeon(argv[2], argv[3]);
    else return -1;

    return 0;
}
