#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>
#include <functional>

class Item
{

public:
    Item(std::string name, std::function<void(std::vector<void*>)> function);
    void doSomething(std::vector<void*> args);

    std::string name;

private:
    unsigned long int uid;
    std::function<void(std::vector<void*>)> _doSomething;
};

#endif