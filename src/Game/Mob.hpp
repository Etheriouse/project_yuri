#ifndef GAME_MOB_HPP
#define GAME_MOB_HPP

#include "Life.hpp"

class Mob : public Life {
public:
    Mob(std::string name, unsigned int hp, unsigned int mana) : Life(name, hp, mana) {
        
    }

};

#endif