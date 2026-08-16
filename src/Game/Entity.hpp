#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include <string>
#include "../Serializer/Serializer.hpp"

class Entity
{

public:

    Entity(std::string name) : name(name)
    {

    }

    unsigned long int uid;
    std::string name;


    virtual void load(Serializer& s) {
        s.load(uid);
        s.load(name);
    }

    virtual void save(Serializer& s) {
        s.save(uid);
        s.save(name);
    }

    virtual void debug_print() {
        std::cout << "uid: " << uid << " name: " << name << std::endl;
    }

};

#endif