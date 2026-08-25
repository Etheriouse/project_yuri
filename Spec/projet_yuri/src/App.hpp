#ifndef GAME_APP_HPP
#define GAME_APP_HPP

#include <cstdint>

#define OneBillion 1'000'000'000.0L
#define TICK_RATE 120.0L
#define TICK_TIME 1.0L/TICK_RATE

typedef struct
{
    uint32_t width, height;
} AppSize;

class App
{

public:
    App();
    App(uint32_t width, uint32_t height, const char *name);
    ~App();

    /* Main function */

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

    /** Width of the app */
    uint32_t width;
    /** Height of the app */
    uint32_t height;

private:
    /**
     * Pointer to a Game object, if nullptr, there is no Game in cours
     */
    int *game;
    /**
     * Object for using menu
     */
    int menu;
    /**
     * Input Ouput gestionnary, like keyboard mouse etc
     */
    int IOgestionnary;
    /**
     * Texture loader unloader etc
     */
    int TexturesGestionnary;
};

#endif