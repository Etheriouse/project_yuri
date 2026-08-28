#ifndef GAME_DUNGEON_HPP
#define GAME_DUNGEON_HPP

#include <cstdint>
#include <vector>

#include "Floor.hpp"

class Player;

class Dungeon
{
public:
    Dungeon();
    Dungeon(Player *p);
    ~Dungeon();

    /**
     * render the game or the actual things used at the screen
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void render(long double delta, uint64_t tick);

    /**
     * Process the game if a game is in court
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void process(long double delta, uint64_t tick);

private:
    std::vector<Floor> floors;

    /** Reference to the player of Game */
    Player *player;

};

#endif