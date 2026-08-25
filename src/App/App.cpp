#include <iostream>
#include <raylib.h>

#include "App.hpp"
#include "Global.hpp"
#include "Time.hpp"

App::App() : App(1600, 900, "Project Yuri") {}

App::App(uint32_t width, uint32_t height, const char *name) : width(width), height(height)
{
    setApp(this);
    InitWindow(width, height, name);
}

App::~App()
{
}

/**
 * ========================= Main function =========================
 */

int App::run()
{

    bool running = true;

    long double delta = 0, acc_s = 0, acc_ds = 0, acc_p = 0;
    uint64_t tick = 0, tick_s = 0, fps = 0, tmp = 0, last = GameTime::getNanoS();

    SetTargetFPS(0);

    while (running && !appIsClosing())
    {
        tmp = GameTime::getNanoS();
        delta = static_cast<long double>(tmp - last) / OneBillion;
        last = tmp;

        // delta caper a 250ms
        if (delta > 0.25L)
            delta = 0.25L;

        acc_p += delta;

        while (acc_p >= TICK_TIME)
        {
            process(delta, tick);
            acc_p -= TICK_TIME;

            tick++;
            tick_s++;
        }

        render(delta, tick);
        fps++;

        acc_s += delta;
        if (acc_s >= 1.0L)
        {
            //std::cout << "process tick: " << tick_s << std::endl;
            tick_s = 0;
            acc_s -= 1.0L;
        }

        acc_ds += delta;
        if(acc_ds >= 0.5L) {
            //std::cout << "fps: " << fps*2 << std::endl;
            fps = 0;
            acc_ds-=0.5L;
        }
    }

    CloseWindow();

    return 0;
}

void App::render(long double delta, uint64_t tick)
{

    unused(delta);
    unused(tick);

    BeginDrawing();
    ClearBackground(WHITE);

    EndDrawing();
}

void App::process(long double delta, uint64_t tick)
{
    unused(delta);
    unused(tick);
}

/**
 * ========================= Getter function =========================
 */

bool App::appIsClosing()
{
    //  std::cout << "not is key down escape : " <<  !IsKeyDown(KEY_ESCAPE) <<  " full condition : " << (WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) << std::endl;
    return WindowShouldClose() && !IsKeyDown(KEY_ESCAPE);
}