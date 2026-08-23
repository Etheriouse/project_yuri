#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "Life.hpp"
#include "Item.hpp"


class Player : public Life {
public:
    Player();
    Player(std::string name, unsigned int hp, unsigned int mana);

    ~Player();

    void load(Serializer& s) override;
    void save(Serializer& s) const override;
    TypeEntity type() override;

    void process(long double delta, uint64_t tick) override;
    void render(long double delta, uint64_t tick) override;

    void debug_print() override;


    // gameplay
    void heal(int64_t value);


    bool had_to_play;
    std::vector<Item> inventory;
};

#endif