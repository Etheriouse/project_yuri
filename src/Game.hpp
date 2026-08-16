#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include "Map/WorldMap.hpp"
#include "Game/Player.hpp"

class Game {

    public:
        Game();
    
        inline unsigned long int get_uid()  {
            return this->uid_counter++;
        }

        inline void new_gameplus() {
            this->ng++;
        }

        void save(Serializer& s);
        void load(Serializer& s);

        void debug_print();

    private:
        unsigned long int uid_counter ;
        unsigned int ng;
        WorldMap *world_map;
        Player *p;

};

#endif