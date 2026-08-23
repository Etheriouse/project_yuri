#ifndef GAME_APPLICATION_HPP
#define GAME_APPLICATION_HPP

#include <cstdint>
#include <map>
#include <string>
#include <thread>
#include <raylib.h>

#include "Map.hpp"

// Forward declaration
class Game;

class Application
{

public:
    Application();
    ~Application();
    int run();
    uint64_t getUID();

    void _LoadTexture();
    void _UnLoadTexture();
    void LoadLanguage();
    void UnLoadLanguage();

    Texture2D getTextureTile(Tile type);

    static inline Application newInstance()
    {
        return Application();
    }

    inline uint64_t getNanoS()
    {
        auto tse = std::chrono::steady_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(tse).count();
    }

    void process_f();
    void render_f();

    inline bool isClosing() { return appIsClosing; }

private:
    unsigned int width = 1600, height = 900;

    unsigned int fps = 144;

    Game *game;
    bool appIsClosing = false;

    std::map<std::string, Texture2D> gestionaryTextures;

    bool running = true;
    std::thread process;
    uint64_t process_tick;
    long double delta;

    std::thread render;
    uint64_t render_tick;
};

#endif