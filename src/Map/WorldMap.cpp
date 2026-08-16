#include "WorldMap.hpp"
#include "../Serializer/Serializer.hpp"

void WorldMap::load(Serializer& s) {
    s.load(map);
}

void WorldMap::save(Serializer& s) {
    s.save(map);
}

void WorldMap::debug_print() {
    std::cout << "map size: " << map.size() << std::endl;
}