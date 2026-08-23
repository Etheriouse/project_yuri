#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include "Game/Player.hpp"
#include <thread>

class Map;

class Game {

    public:
        Game();
    
        inline unsigned long int get_uid()  {
            return this->uid_counter++;
        }

        inline void new_gameplus() {
            this->ng++;
        }

        // when fisrt time run new save;
        void new_game(std::string filename);
        void run();
        void process_f();
        void render_f();

        void save(Serializer& s) const;
        void load(Serializer& s);

        void debug_print();

    private:

        // to save to disk
        unsigned long int uid_counter;
        unsigned int ng;

        Player p;

        // to not save to disk
        bool running = true;

        std::thread process;
        uint64_t process_tick;
        long double delta;

        std::thread render;
        uint64_t render_tick;


};

#endif