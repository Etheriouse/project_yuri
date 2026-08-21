#include "Map.hpp"
#include "../Serializer/Serializer.hpp"
#include "../Game/Mob.hpp"

Map::Map(std::string filename, Player *p) : p(p)
{
    // read width height
    Serializer s(filename, SERIALIZER_LOAD_MODE);
    s.load(width);
    s.load(height);
    s.load(this->map);
    size_t nb_entitys = 0;
    s.load(nb_entitys);
    TypeEntity type;
    unsigned int x, y;
    std::unique_ptr<Entity> entity;
    for (size_t i = 0; i < nb_entitys; i++)
    {
        s.load(type);
        std::cout << type << std::endl;
        switch (type)
        {
        case TypeEntity::_Mob:
            entity = std::make_unique<Mob>();
            break;

        case TypeEntity::_Player:
            entity = std::make_unique<Player>();
            break;

        case TypeEntity::_Life:
            entity = std::make_unique<Life>();
            break;

        case TypeEntity::_Entity:
            entity = std::make_unique<Entity>();
        default:
            break;
        }
        s.load(*entity);
        s.load(x);
        s.load(y);
        this->things.push_back({y, x, entity.get()});
        entity.get()->debug_print();
    }
}

Map::Map(unsigned int _width, unsigned int _height, Player *p, std::vector<MapEntity> things)
    : width(_width), height(_height), map(width * height), things(things), p(p), is_active(false)
{
    // for(const e : things)

    // place the things and the thongs little randomly into the cell map
}

Map::~Map()
{
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
    for (MapEntity e : things)
        e.entity->process(delta, tick);
}

void Map::render(long double delta, uint64_t tick)
{
    for (MapEntity e : things)
        e.entity->render(delta, tick);
}

void Map::debug_print()
{
    size_t j = 0;
    size_t i = 0;
    for (Cell c : map)
    {

        // if (c.entitys.size() > 0)
        //     std::cout << "[";
        // else
        //     std::cout << " ";

        if (c.type == TypeTile::Floor)
            std::cout << "_";
        else if (c.type == TypeTile::Wall)
            std::cout << "#";
        else
            std::cout << "E";

        // if (c.entitys.size() > 0)
        //     std::cout << "[";
        // else
        //     std::cout << " ";

        j++;

        if (j == width)
        {
            std::cout << '\n';
            j = 0;
            i++;
        }
    }
}


void Map::save(Serializer &s) {
    s.save(width);
    s.save(height);
    s.save(map);
    s.save(things.size());
    for (MapEntity e : things)
    {
        s.save(e.entity->type());
        s.save(*e.entity);
        s.save(e.x);
        s.save(e.y);
    }
}