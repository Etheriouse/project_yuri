#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <raylib.h>

class Window
{

public:
    Window* Create()
    {
        InitWindow(1920, 1080, "Affiche toi ou jte bute");

        return this;
    }

    void run()
    {
        while (!WindowShouldClose())
        {
            this->doSomething();
        }

        CloseWindow();
    }

    void doSomething()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello Raylib", 300, 280, 20, BLACK);
        EndDrawing();
    }

private:
};

#endif