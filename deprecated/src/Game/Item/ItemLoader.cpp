#include "ItemLoader.hpp"
#include <map>
#include "Entity.hpp"
#include "Mob.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

void f_Estus(Entity *target, Entity *source, std::vector<int64_t> args);
void f_Seppuku(Entity *target, Entity *source, std::vector<int64_t> args);

const map<ItemType, ItemFunction> itemLibrary = {
    {ItemType::Default, [](Entity *target, Entity *source, std::vector<int64_t> args)
     {
         // default do nothing
     }},
    {ItemType::Seppuku, f_Seppuku},
    {ItemType::Estus, f_Estus}
};

ItemFunction getDoSomething(ItemType type)
{
    const auto index = itemLibrary.find(type);
    if (index == itemLibrary.end())
        return itemLibrary.at(ItemType::Default);
    return index->second;
}

void f_Estus(Entity *target, Entity *source, std::vector<int64_t> args)
{
    dynamic_cast<Player *>(target)->heal(args[0]);
}

void f_Seppuku(Entity *target, Entity *source, std::vector<int64_t> args)
{
    dynamic_cast<Player *>(target)->heal(args[0]);
}
