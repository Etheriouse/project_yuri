
#ifndef GAME_GLOBAL_HPP
#define GAME_GLOBAL_HPP

#include <cstdint>

class App;

extern App *g_app;

void setApp(App *ptr);

typedef struct
{
    float x, y;
} Coordinate;

typedef struct
{
    uint16_t w, h;
} Size;

inline Coordinate asytoPixel(Coordinate p, Size s)
{
    return {
        (p.x - p.y) * s.w / 2,
        (p.x + p.y) * (s.h / 4)};
}

inline Coordinate pixelToAsy(Coordinate p, Size s)
{
    return {
        (p.x / (s.w / 2) + p.y / (s.h / 2)) / 2,
        (p.y / (s.h / 2) - p.x / (s.w / 2)) / 2};
}

#endif