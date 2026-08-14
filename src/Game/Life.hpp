#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include "Entity.hpp"

class Life : public Entity
{

public:
    Life(std::string name, unsigned int hp, unsigned int mana) : Entity(name), hp(hp), mana(mana){};

    unsigned int hp, mana;
};

#endif