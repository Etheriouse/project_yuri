#ifndef GAME_DUNGEON_HPP
#define GAME_DUNGEON_HPP

#include <vector>
#include "Map.hpp"

class Dungeon
{

public:
    Dungeon();

    inline void nextFloor() {
        if(floor >= rooftop) return exit();
        floors[floor]->exit();
        floor++;
        floors[floor]->enter(p);
    }

    inline void exit() {
        active = false;
    }

    inline void enter(Player *_p) {
        active = true;
        floor = 0;
        p = _p;
        floors[floor]->enter(p);
    }

    inline bool isActive() {
        return active;
    }
    
    void process(long double delta, uint64_t tick);
    void render(long double delta, uint64_t tick);

private:
    Player *p;

    uint64_t floor;
    uint64_t rooftop;

    bool active = false;
    std::vector<Map *> floors;
};

#endif