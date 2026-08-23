#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>
#include <functional>
#include <vector>

class Entity;
class Serializer;

typedef std::function<void(Entity* target, Entity* source, std::vector<int64_t> args)> ItemFunction;

enum ItemType
{
    Default,
    Estus,
    Seppuku,
};

class Item
{

public:
    Item();
    Item(std::string name, ItemType type);
    void doSomething(Entity* target, Entity* source, std::vector<int64_t> args);


    void load(Serializer &s);
    void save(Serializer &s) const;

    std::string name;

private:
    uint64_t uid;
    ItemType type;
    ItemFunction _doSomething;
};

#endif