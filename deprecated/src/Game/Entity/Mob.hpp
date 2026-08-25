#ifndef GAME_MOB_HPP
#define GAME_MOB_HPP

#include "Life.hpp"

class Mob : public Life {
public:

    Mob();
    Mob(std::string name, unsigned int hp, unsigned int mana);

    ~Mob();

    void load(Serializer &s) override;
    void save(Serializer &s) const override;

    
    void process(long double delta, uint64_t tick) override;
    void render(long double delta, uint64_t tick) override;

    TypeEntity type() override;
    void debug_print() override;

};

#endif