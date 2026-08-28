#include <string>
#include <iostream>

#include "MapMaker.hpp"
#include "DungeonMaker.hpp"

int main(int argc, char const *argv[])
{
    if(argc != 3) return -1;

    if(argv[1] == std::string("map")) makeMap(argv[2]);
    else if(argv[1] == std::string("dungeon")) makeDungeon(argv[2]);
    else return -1;

    return 0;
}
