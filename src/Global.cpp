#include "Global.hpp"

Game g_game = Game();

void set_game(std::string filename) {
    Serializer s(filename, LOAD_MODE);
    g_game.load(s);
}

void save_game(std::string filename) {
    Serializer s(filename, SAVE_MODE);
    g_game.save(s);
}

