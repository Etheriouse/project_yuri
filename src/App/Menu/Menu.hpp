#ifndef APP_MENU_HPP
#define APP_MENU_HPP

#include <cstdint>

#include "Game.hpp"

#define unused(x) (void)(x)

/* Menu load a game and create with new */
/* Menu unload a game and set to nullptr */

class Menu
{

public:
    Menu();
    Menu(bool *runningApp, Game **gameApp);

    ~Menu();

    /**
     * render the game or the actual things used at the screen
     * @param delta time between last frame
     * @param tick number tick elapsed from the launch of app
     */
    void render(long double delta, uint64_t tick);

private:
    bool *runningApp;
    /**
     * Ptr to the game variable of the app
     */
    Game **gameApp;
};

#endif