#include "Game.hpp"
#include "Game/Player.hpp"
#include "Serializer/Serializer.hpp"

Game::Game() : uid_counter(0), ng(1) {
    // create player
    // find worldmap

    this->p = new Player("player", 10, 10);
    this->world_map = new WorldMap();
}

void Game::load(Serializer& s) {
    s.load(this->ng);
    s.load(this->uid_counter);
    p->load(s);
    world_map->load(s);
}

void Game::save(Serializer& s) {
    s.save(this->ng);
    s.save(this->uid_counter);
    p->save(s);
    world_map->save(s);
}

void Game::debug_print() {
    std::cout << "ng: " << ng << std::endl << "uid counter: " << uid_counter << std::endl;
    p->debug_print();
    world_map->debug_print();
}