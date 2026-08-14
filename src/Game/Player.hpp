#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "Life.hpp"

class Player : public Life {
public:
    Player(std::string name, unsigned int hp, unsigned int mana) : Life(name, hp, mana) {

    }

};

#endif