#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "Life.hpp"

class Player : public Life {
public:
    Player(std::string name, unsigned int hp, unsigned int mana) : Life(name, hp, mana) {

    }

    void load(Serializer& s) override {
        Life::load(s);
    }

    void save(Serializer& s) override {
        Life::save(s);
    }

    void debug_print() override {
        Life::debug_print();
    }

};

#endif