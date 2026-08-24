#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include "Player.hpp"
#include "Dungeon.hpp"
#include <thread>


class Game {

    public:
        Game();
        ~Game();
    
        inline uint64_t _getUID()  {
            return this->uid_counter++;
        }

        inline void new_gameplus() {
            this->ng++;
        }


        // when fisrt time run new save;
        void new_game(std::string filename);
        void run();
        void process(double delta, uint64_t tick);
        void render(double delta, uint64_t tick);

        void save(Serializer& s) const;
        void load(Serializer& s);

        void debug_print();

    private:

        // to save to disk
        unsigned long int uid_counter = 0;
        unsigned int ng = 0;

        Player p;
        
        // to not save to disk
        Dungeon *dungeon_act;

};

#endif