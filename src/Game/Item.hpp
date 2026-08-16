#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>
#include <functional>

#include "../Global.hpp"

class Item
{

public:
    Item(std::string name, std::function<void(std::vector<void*>)> function)
        : name(name), _doSomething(function)
    {
        this->uid = g_game.get_uid();
    }

    void doSomething(std::vector<void*> args)
    {
        _doSomething(args);
    }

    std::string name;

private:
    unsigned long int uid;
    std::function<void(std::vector<void*>)> _doSomething;
};

#endif