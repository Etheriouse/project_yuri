#include "Serializer/Serializer.hpp"
#include "Item.hpp"
#include "ItemLoader.hpp"
#include "Entity.hpp"

#include "Global.hpp"

Item::Item() : name("undefined"), type(ItemType::Default)
{
    uid = app->getUID();
    _doSomething = getDoSomething(type);
}

Item::Item(std::string name, ItemType type)
    : name(name), type(type)
{
    uid = app->getUID();
    _doSomething = getDoSomething(type);
}

void Item::doSomething(Entity *target, Entity *source, std::vector<int64_t> args)
{
    _doSomething(target, source, args);
}

void Item::load(Serializer &s)
{
    s.load(name);
    s.load(type);
    s.load(uid);

    _doSomething = getDoSomething(type);
}

void Item::save(Serializer &s) const
{
    s.save(name);
    s.save(type);
    s.save(uid);
}