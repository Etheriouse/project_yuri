#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>
#include <functional>

class Item
{

public:
    Item(std::string name, std::function<void(std::vector<void*>)> function)
        : name(name), _doSomething(function)
    {
    }

    void doSomething(std::vector<void*> args)
    {
        _doSomething(args);
    }

    std::string name;

private:
    std::function<void(std::vector<void*>)> _doSomething;
};

#endif