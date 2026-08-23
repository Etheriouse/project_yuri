#include "Application.hpp"
#include "Game.hpp"
#include "Global.hpp"
#include "Serializer.hpp"
#include <iostream>

using namespace std;

Application::Application()
{
    setApp(this);
    InitWindow(width, height, "Game");
    _LoadTexture();
    LoadLanguage();

    game = new Game();
    Serializer s("game.rrl", SERIALIZER_LOAD_MODE);
    game->load(s);
    game->run();
}

Application::~Application()
{
    delete game;
}

int Application::run()
{
    cout << "Hello world Game !" << endl
         << "Game is launching. . ." << endl;

    SetTargetFPS(fps);

    process = std::thread(&Application::process_f, this);

    render_f();
    process.join();
    

    UnLoadLanguage();
    _UnLoadTexture();
    CloseWindow();

    cout << "Game is stopped" << endl
         << "Goodbye" << endl;
    return 0;
}

uint64_t Application::getUID()
{
    if (game != nullptr)
        return game->_getUID();
    return 0;
}

void Application::_LoadTexture()
{
    gestionaryTextures["default"] = LoadTexture("assets/tiles/default.png");
    gestionaryTextures["grass_tile"] = LoadTexture("assets/tiles/grass.png");
    gestionaryTextures["stone_tile"] = LoadTexture("assets/tiles/stone.png");
    gestionaryTextures["wood_bridge_tile"] = LoadTexture("assets/tiles/wood_bridge.png");
}

void Application::_UnLoadTexture()
{
    for (auto &[key, value] : gestionaryTextures)
    {
        UnloadTexture(value);
    }
}

void Application::LoadLanguage()
{
}

void Application::UnLoadLanguage()
{
}

Texture2D Application::getTextureTile(Tile type)
{
    switch (type)
    {
    case Tile::Grass:
        return gestionaryTextures["grass_tile"];

    case Tile::Stone:
        return gestionaryTextures["stone_tile"];

    case Tile::WoodBridge:
        return gestionaryTextures["wood_bridge_tile"];

    case Tile::Air:
        return gestionaryTextures["air_tile"];

    case Tile::Void:
        return gestionaryTextures["void_tile"];

    default:
        return gestionaryTextures["default"];
    }
}


void Application::process_f()
{

    uint64_t tmp = 0, last = getNanoS();

    unsigned int tick_s = 0;
    long double acc_s = 0;

    while (running && !app->isClosing())
    {
        tmp = getNanoS();
        delta = ((long double)(tmp - last)) / 1'000'000'000.0L;
        last = tmp;

        acc_s += delta;

        if(game != nullptr) {
            game->process(delta, process_tick);
        }

        if (acc_s > 1)
        {
            std::cout << "process tick: " << tick_s << std::endl;
            tick_s = 0;
            acc_s = 0;
        }

        tick_s++;
        process_tick++;
    }
}

void Application::render_f()
{
    uint64_t tmp = 0, last = getNanoS();

    unsigned int tick_s = 0;
    long double acc_s = 0;

    while (running && !app->isClosing())
    {
        tmp = getNanoS();
        delta = ((long double)(tmp - last)) / 1'000'000'000.0L;
        last = tmp;

        acc_s += delta;

        BeginDrawing();
        ClearBackground(WHITE);
        if(game != nullptr) {
            game->render(delta, render_tick);
        }
       
        EndDrawing();

        if (acc_s > 1)
        {
            std::cout << "fps: " << tick_s << std::endl;
            tick_s = 0;
            acc_s = 0;
        }

        tick_s++;
        render_tick++;
        appIsClosing = WindowShouldClose();
    }
}