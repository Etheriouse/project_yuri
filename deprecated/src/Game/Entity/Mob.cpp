#include "Mob.hpp"
#include <iostream>

Mob::Mob() : Life() {};

Mob::Mob(std::string name, unsigned int hp, unsigned int mana) : Life(name, hp, mana)
{
}

Mob::~Mob() {

}

void Mob::load(Serializer &s) {
    Life::load(s);
}
void Mob::save(Serializer &s) const {
    Life::save(s);
}


void Mob::process(long double delta, uint64_t tick) {

}

void Mob::render(long double delta, uint64_t tick) {

}

TypeEntity Mob::type()
{
    return TypeEntity::_Mob;
}

void Mob::debug_print() {
    std::cout << "mob" << std::endl;
    Life::debug_print();
}