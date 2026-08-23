#include "Global.hpp"
#include "Serializer/Serializer.hpp"

Game g_game = Game();


void firstTimeGame(std::string filename);

void set_game(std::string filename) {
    Serializer s(filename, SERIALIZER_LOAD_MODE);
    try {
        g_game.load(s);
    } catch(std::bad_alloc) {
        firstTimeGame(filename);
    }
}

void save_game(std::string filename) {
    Serializer s(filename, SERIALIZER_SAVE_MODE);
    g_game.save(s);
}

void firstTimeGame(std::string filename) {
    g_game.new_game(filename);
    set_game(filename);
}


