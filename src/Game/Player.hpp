#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "Life.hpp"


class Player : public Life {
public:
    Player();
    Player(std::string name, unsigned int hp, unsigned int mana);

    void load(Serializer& s) override;
    void save(Serializer& s) const override;
    TypeEntity type() override;

    void process(long double delta, uint64_t tick) override;
    void render(long double delta, uint64_t tick) override;


    void debug_print() override;

    unsigned long int p_x, p_y;
};

#endif