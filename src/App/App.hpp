#ifndef APP_APP_HPP
#define APP_APP_HPP

#include <cstdint>

#include "Game.hpp"
#include "Menu.hpp"
#include "IOGestionnary.hpp"
#include "TexturesGestionnary.hpp"
#include "Serializer.hpp"

#define OneBillion 1'000'000'000.0L
#define TICK_RATE 120.0L
#define TICK_TIME 1.0L/TICK_RATE

#define unused(x) (void)(x)

class App
{

    App();
    App(uint32_t width, uint32_t height, const char *name);
public:
    ~App();

    /* Main function */

    /**
     * Create a app in reading settings of app in file app.settings
     */
    static inline App create() {
        Serializer::Reader file("app.settings");
        uint32_t width, height;
        std::string name;
        file.read(width);
        file.read(height);
        file.read(name);
        return App(width, height, name.c_str());
    }

    /**
     * Run the main loop of the application, load and unload all
     */
    int run();

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

    /* Getter function */

    /**
     * Return if the app is closing
     */
    bool appIsClosing();

    /**
     * Size of app
     */
    inline Size size() {
        return {width, height};
    }

    /** Width of the app */
    uint16_t width;
    /** Height of the app */
    uint16_t height;

    /**
     * Texture loader unloader etc
     */
    TextureGestionnary TexturesGestionnary;

private:

    /**
     * Value who manage the life of the app
     */
    bool running = true;

    /**
     * Pointer to a Game object, if nullptr, there is no Game in cours
     */
    Game *game = nullptr;
    /**
     * Object for using menu
     */
    Menu menu;
    /**
     * Input Ouput gestionnary, like keyboard mouse etc
     */
    IOGestionnary IOgestionnary;
};

#endif