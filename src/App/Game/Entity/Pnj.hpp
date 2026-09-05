#ifndef GAME_PNJ_HPP
#define GAME_PNJ_HPP

#include <string>

#include "Serializer.hpp"

class Pnj
{

public:
    void write(Serializer::Writer &w) const
    {
        w.write(uidDialogue);
        w.write(texture);
        w.write(name);
        w.write(x);
        w.write(y);
    }

    void read(Serializer::Reader &r)
    {
        r.read(uidDialogue);
        r.read(texture);
        r.read(name);
        r.read(x);
        r.read(y);
    }

private:
    uint64_t uidDialogue;
    std::string texture, name;
    uint16_t x, y;
};

#endif