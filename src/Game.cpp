#include "Game.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Serializer.hpp"
#include "Global.hpp"

#include <raylib.h>

Game::Game() : uid_counter(0), ng(1)
{
    // create player
    // find worldmapyun

    this->p = Player("player", 10, 10);
}

void Game::new_game(std::string filename)
{
    p = Player("player", 10, 10);
    Serializer s(filename, SERIALIZER_SAVE_MODE);
    save(s);
}

void Game::run()
{
    p = Player("player", 10, 10);

    dungeon_act = new Dungeon();
    dungeon_act->enter(&p);
}

void Game::process(double delta, uint64_t tick)
{
    if (dungeon_act != nullptr && dungeon_act->isActive())
    {
        dungeon_act->process(delta, tick);
    }
}
void Game::render(double delta, uint64_t tick)
{
    if (dungeon_act != nullptr && dungeon_act->isActive())
    {
        dungeon_act->render(delta, tick);
    }
}

void Game::load(Serializer &s)
{
    s.load(this->ng);
    s.load(this->uid_counter);
    p.load(s);
}

void Game::save(Serializer &s) const
{
    s.save(this->ng);
    s.save(this->uid_counter);
    p.save(s);
}

void Game::debug_print()
{
    std::cout << "ng: " << ng << std::endl
              << "uid counter: " << uid_counter << std::endl;
    p.debug_print();
}