#include "Life.hpp"
#include "Serializer/Serializer.hpp"

Life::Life() : Entity(), hp(10), mana(5) {};

Life::Life(std::string name, unsigned int hp, unsigned int mana) : Entity(name), hp(hp), mana(mana) {};

void Life::load(Serializer &s)
{
    Entity::load(s);
    s.load(hp);
    s.load(mana);
}

void Life::save(Serializer &s) const
{
    Entity::save(s);
    s.save(hp);
    s.save(mana);
}

TypeEntity Life::type() {
    return TypeEntity::_Life;
}

void Life::process(long double delta, uint64_t tick) {}
void Life::render(long double delta, uint64_t tick) {}

void Life::debug_print()
{
    Entity::debug_print();
    std::cout << "hp: " << hp << " mana: " << mana << std::endl;
}
