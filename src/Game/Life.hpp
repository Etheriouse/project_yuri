#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include "Entity.hpp"

class Life : public Entity
{

public:
    Life(std::string name, unsigned int hp, unsigned int mana) : Entity(name), hp(hp), mana(mana){};

    void load(Serializer& s) override {
        Entity::load(s);
        s.load(hp);
        s.load(mana);
    }

    void save(Serializer& s) override {
        Entity::save(s);
        s.save(hp);
        s.save(mana);
    }

    void debug_print() override {
        Entity::debug_print();
        std::cout << "hp: " << hp << " mana: " << mana << std::endl;
    }

    unsigned int hp, mana;
};

#endif