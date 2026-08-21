#include "Entity.hpp"
#include "../Serializer/Serializer.hpp"

Entity::Entity() : name("undefined") {

}

Entity::Entity(std::string name) : name(name)
{
}

void Entity::load(Serializer &s)
{
    s.load(uid);
    s.load(name);
}

void Entity::save(Serializer &s) const
{
    s.save(uid);
    s.save(name);
}

TypeEntity Entity::type() {
    return TypeEntity::_Entity;
}

void Entity::process(long double delta, uint64_t tick) {}
void Entity::render(long double delta, uint64_t tick) {}

void Entity::debug_print()
{
    std::cout << "uid: " << uid << " name: " << name << std::endl;
}