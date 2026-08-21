#include "Global.hpp"
#include "Serializer/Serializer.hpp"

Game g_game = Game();

void set_game(std::string filename) {
    Serializer s(filename, SERIALIZER_LOAD_MODE);
    g_game.load(s);
}

void save_game(std::string filename) {
    Serializer s(filename, SERIALIZER_SAVE_MODE);
    g_game.save(s);
}

