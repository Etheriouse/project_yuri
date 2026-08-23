#include "Entity.hpp"
#include "Serializer/Serializer.hpp"
#include "Global.hpp"

Entity::Entity() : name("undefined") {
    uid = app->getUID();
}

Entity::Entity(std::string name) : name(name)
{
    uid = app->getUID();
}

Entity::~Entity() {

}


void Entity::load(Serializer &s)
{
    s.load(uid);
    s.load(name);
    s.load(x);
    s.load(y);
}

void Entity::save(Serializer &s) const
{
    s.save(uid);
    s.save(name);
    s.save(x);
    s.save(y);
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