#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include "Entity.hpp"

class Life : public Entity
{

public:
    Life();
    Life(std::string name, unsigned int hp, unsigned int mana);

    ~Life();

    void load(Serializer& s) override;
    void save(Serializer& s) const override;
    TypeEntity type() override;

    void process(long double delta, uint64_t tick) override;
    void render(long double delta, uint64_t tick) override;

    void debug_print() override;

    unsigned int hp, hpmax, mana, manamax;
};

#endif