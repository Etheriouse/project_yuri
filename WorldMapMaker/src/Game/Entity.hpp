#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>

class Serializer;

enum TypeEntity {
    _Entity,
    _Life,
    _Player,
    _Mob
};

class Entity
{

public:

    Entity();
    Entity(std::string name);

    unsigned long int uid;
    std::string name;


    virtual void load(Serializer& s);
    virtual void save(Serializer& s) const;
    virtual TypeEntity type();

    virtual void process(long double delta, uint64_t tick);
    virtual void render(long double delta, uint64_t tick);

    virtual void debug_print();

};

#endif