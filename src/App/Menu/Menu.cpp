#include "Menu.hpp"

Menu::Menu() {

}

Menu::Menu(bool *runningApp, Game **gameApp) : runningApp(runningApp), gameApp(gameApp) {

}

Menu::~Menu() {

}

void Menu::render(long double delta, uint64_t tick) {
    unused(delta);
    unused(tick);

    // printf("its meee");
}