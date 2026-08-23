#include "Map.hpp"
#include "../Serializer/Serializer.hpp"
#include "../Game/Mob.hpp"

Map::Map(std::string filename, Player *p) : p(p)
{
    Serializer s(filename, SERIALIZER_LOAD_MODE);
    load(s);
}

Map::Map(unsigned int _width, unsigned int _height, Player *p, std::vector<Entity *> things)
    : width(_width), height(_height), map(width * height), things(things), p(p), is_active(false)
{
    // do procedural things
}

Map::~Map()
{
    for(auto e : things) {
        delete e;
    }
}

inline Cell *Map::get(unsigned int x, unsigned int y)
{
    return &this->map[y * width + x];
}

void Map::run()
{
    is_active = true;
}

void Map::exit()
{
    is_active = false;
}

void Map::process(long double delta, uint64_t tick)
{
    for (Entity *e : things)
        e->process(delta, tick);
}

void Map::render(long double delta, uint64_t tick)
{
    for (Entity *e : things)
        e->render(delta, tick);
}

void Map::debug_print()
{
    size_t j = 0;
    size_t i = 0;
    for (uint i = 0; i < height; i++)
    {
        for (uint j = 0; j < width; j++)
        {
            Cell c = map[i * width + j];
            if (c.type == Tile::Floor)
                std::cout << "_";
            else if (c.type == Tile::Wall)
                std::cout << "#";
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
    std::unique_ptr<Entity> entity;
    for (size_t i = 0; i < nb_entitys; i++)
    {
        s.load(type);
        switch (type)
        {
        case TypeEntity::_Mob:
            entity = std::make_unique<Mob>();
            break;

        case TypeEntity::_Life:
            entity = std::make_unique<Life>();
            break;

        default:
            entity = std::make_unique<Entity>();
            break;
        }
        s.load(*entity);
        this->things.push_back(entity.get());
    }
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
        s.save(e->x);
        s.save(e->y);
    }
}