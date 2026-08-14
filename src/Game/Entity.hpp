#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>

class Entity
{

public:
    Entity(std::string name) : name(name)
    {
    }
    std::string name;
};

#endif