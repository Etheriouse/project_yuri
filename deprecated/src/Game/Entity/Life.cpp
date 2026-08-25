#include "Life.hpp"
#include "Serializer.hpp"

Life::Life() : Entity(), hp(10), mana(5) {};

Life::Life(std::string name, unsigned int hpmax, unsigned int manamax) : Entity(name), hp(hpmax), hpmax(hpmax), mana(manamax), manamax(manamax) {};

Life::~Life() {
    }

void Life::load(Serializer &s)
{
    Entity::load(s);
    s.load(hp);
    s.load(hpmax);
    s.load(mana);
    s.load(manamax);
}

void Life::save(Serializer &s) const
{
    Entity::save(s);
    s.save(hp);
    s.save(hpmax);
    s.save(mana);
    s.save(manamax);
}

TypeEntity Life::type() {
    return TypeEntity::_Life;
}

void Life::process(long double delta, uint64_t tick) {}
void Life::render(long double delta, uint64_t tick) {}

void Life::debug_print()
{
    Entity::debug_print();
    std::cout << "hp: " << hp << "/" <<  hpmax << " mana: " << mana << "/" << manamax << std::endl;
}
