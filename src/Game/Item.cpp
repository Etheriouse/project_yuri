#include "../Global.hpp"
#include "Item.hpp"

Item::Item(std::string name, std::function<void(std::vector<void *>)> function)
    : name(name), _doSomething(function)
{
    this->uid = g_game.get_uid();
}

void Item::doSomething(std::vector<void *> args)
{
    _doSomething(args);
}