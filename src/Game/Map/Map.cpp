#include "Map.hpp"
#include "Serializer.hpp"
#include "Mob.hpp"
#include "Global.hpp"

#include <raylib.h>

Map::Map(std::string filename)
{
    Serializer s(filename, SERIALIZER_LOAD_MODE);
    load(s);
    start_draw_x = (app->size().width / 2) - tile_width / 2;
    start_draw_y = 0;
}

Map::Map(unsigned int _width, unsigned int _height, std::vector<Entity *> things)
    : width(_width), height(_height), map(width * height), things(things), is_active(false)
{
    // do procedural things
}

Map::~Map()
{
    if (create_from_file)
    {
        for (auto e : things)
        {
            delete e;
        }
    }
}

void Map::enter(Player *_p)
{
    p = _p;
    is_active = true;
}

void Map::exit()
{
    is_active = false;
}

void Map::process(long double delta, uint64_t tick)
{

    if (p->had_to_play)
    {
        for (Entity *e : things)
        {
            e->process(delta, tick);
        }
    }
}

void Map::render(long double delta, uint64_t tick)
{
    Texture2D tmp;
    AppSize as = app->size();
    float final_x, final_y, push = 1.2f;
    int binf_map_game = as.width * 0.25 + (tile_width / 2);
    int bsup_map_game = as.width * 0.75 - (tile_width / 2);
    // do 0 0 at center top
    for (float y = 0; y < height; y++)
    {
        for (float x = 0; x < width; x++)
        {
            Coordinate cdp = asytoPixel({x, y});
            final_x = cdp.x * push + start_draw_x;
            final_y = cdp.y * push + start_draw_y;
            if (!(final_x + tile_width > binf_map_game && final_x < bsup_map_game))
                continue;
            if (final_y + tile_height > as.height || final_y < 0)
                continue;
            tmp = app->getTextureTile(map[y * width + x].type);
            DrawTexturePro(tmp, {0, 0, (float)tmp.width, (float)tmp.height}, {final_x, final_y, tile_width, tile_height}, {0, 0}, 0.0f, WHITE);

            DrawText((std::to_string((int)x) + ", " + std::to_string((int)y)).c_str(), (start_draw_x) * 1.2f, (cdp.y + start_draw_y) * 1.2f, 15, BLUE);
        }
    }

    DrawLine(as.width * 0.25, 0, as.width * 0.25, as.height, RED);
    DrawLine(as.width * 0.75, 0, as.width * 0.75, as.height, RED);

    for (Entity *e : things)
        e->render(delta, tick);

    std::cout << "delta " << delta << std::endl;
    std::cout << "delta value speed " << delta * SPEED << std::endl;

    if (app->_IsKeyDown(KEY_W))
    {
        start_draw_y -= (delta * SPEED);
    }
    if (app->_IsKeyDown(KEY_S))
    {
        start_draw_y += (delta * SPEED);
    }
    if (app->_IsKeyDown(KEY_A))
    {
        start_draw_x -= (delta * SPEED);
    }
    if (app->_IsKeyDown(KEY_D))
    {
        start_draw_x += (delta * SPEED);
    }
}

void Map::debug_print()
{
    for (uint i = 0; i < height; i++)
    {
        for (uint j = 0; j < width; j++)
        {
            Cell c = map[i * width + j];
            if (c.type == Tile::Grass)
                std::cout << "\"";
            else if (c.type == Tile::Stone)
                std::cout << "#";
            else if (c.type == Tile::WoodBridge)
                std::cout << "-";
            else if (c.type == Tile::Air)
                std::cout << " ";
            else if (c.type == Tile::Void)
                std::cout << "x";
            else
                std::cout << "E";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Map::load(Serializer &s)
{
    s.load(width);
    s.load(height);
    s.load(this->map);
    size_t nb_entitys = 0;
    s.load(nb_entitys);
    TypeEntity type;
    Entity *entity;
    for (size_t i = 0; i < nb_entitys; i++)
    {
        s.load(type);
        switch (type)
        {
        case TypeEntity::_Mob:
            entity = new Mob();
            break;

        case TypeEntity::_Life:
            entity = new Life();
            break;

        default:
            entity = new Entity();
            break;
        }
        s.load(*entity);
        things.push_back(entity);
    }
    create_from_file = true;
}

void Map::save(Serializer &s)
{
    s.save(width);
    s.save(height);
    s.save(map);
    s.save(things.size());
    for (Entity *e : things)
    {
        s.save(e->type());
        s.save(*e);
    }
}