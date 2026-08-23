#include "Map.hpp"
#include "Serializer.hpp"
#include "Mob.hpp"
#include "Global.hpp"

#include <raylib.h>

Map::Map(std::string filename)
{
    Serializer s(filename, SERIALIZER_LOAD_MODE);
    load(s);
}

Map::Map(unsigned int _width, unsigned int _height, std::vector<Entity *> things)
    : width(_width), height(_height), map(width * height), things(things), is_active(false)
{
    // do procedural things
}

Map::~Map() {
    if(create_from_file) {
        for(auto e : things) {
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
    if(p->had_to_play) {
        for (Entity *e : things) {
            e->process(delta, tick);
        }
    }
    
}

void Map::render(long double delta, uint64_t tick)
{
       Texture2D tmp;
    float start_x = 400, start_y = 100;
    for(float y = 0; y<height; y++) {
        for(float x = 0; x<width; x++) {
            tmp = app->getTextureTile(map[y*width+x].type);
            Coordinate cdp = asytoPixel({x, y});
            DrawTexturePro(tmp, {0,0,(float)tmp.width, (float)tmp.height}, {cdp.x+start_x, cdp.y+start_y, tile_width, tile_height}, {0, 0}, 0.0f, WHITE);
        }
    }

    for (Entity *e : things)
        e->render(delta, tick);
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