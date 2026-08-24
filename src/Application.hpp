#ifndef GAME_APPLICATION_HPP
#define GAME_APPLICATION_HPP

// standar things
#include <cstdint>
#include <map>
#include <string>

// thread things
#include <atomic>
#include <thread>

// game
#include <raylib.h>
#include "Map.hpp"

// Forward declaration
class Game;

typedef struct {
    unsigned int width, height;
} AppSize;

#define KEY_COUNT 349

typedef struct {
    std::vector<bool> keydown;
} KeybordState;

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

    inline AppSize size() {
        return {width, height};
    }

    void process_f();
    void render_f();

    bool _IsKeyDown(KeyboardKey k);

    void process_raylib();

    inline bool isClosing() { return appIsClosing; }
    inline void setClosing() { appIsClosing = true; }

private:
    unsigned int width = 1600, height = 900;

    unsigned int fps = 144;

    Game *game;
    bool appIsClosing = false;

    std::map<std::string, Texture2D> gestionaryTextures;
    KeybordState gestionaryKeyboard; // TODO a modifier avec le stysteme 2 etat du jeu

    bool running = true;
    std::thread process;
    uint64_t process_tick;
    long double delta_r;
    long double delta_p;

    std::thread render;
    uint64_t render_tick;
};

#endif