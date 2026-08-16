#ifndef GAME_WORLD_MAP_HPP
#define GAME_WORLD_MAP_HPP

#include <vector>

class Serializer;

typedef struct {
    unsigned int type;
} WorldCell;

class WorldMap {

    public:
        WorldMap() {}

        void load(Serializer& s);
        void save(Serializer& s);

        void debug_print();

    private:
        std::vector<WorldCell> map;

};

#endif