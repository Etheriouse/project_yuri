#include "ItemLoader.hpp"
#include <map>
#include "Entity.hpp"
#include "Mob.hpp"
#include "Player.hpp"

using namespace std;

void f_Estus(Entity *target, Entity *source, std::vector<uint64_t> args);

const map<ItemType, ItemFunction> itemLibrary = {
    {ItemType::Default, [](Entity *target, Entity *source, std::vector<uint64_t> args) {
        // default do nothing
     }},
    {ItemType::Estus, f_Estus}};

ItemFunction getDoSomething(ItemType type)
{
    const auto index = itemLibrary.find(type);
    if (index == itemLibrary.end())
        return itemLibrary.at(ItemType::Default);
    return index->second;
}

void f_Estus(Entity *target, Entity *source, std::vector<uint64_t> args)
{
    dynamic_cast<Player *>(target)->heal(args[0]);
}
