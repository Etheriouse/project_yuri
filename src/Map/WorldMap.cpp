#include "WorldMap.hpp"

#include "../Serializer/Serializer.hpp"
#include "../Game/Player.hpp"
#include "../Game/Entity.hpp"

WorldMap::WorldMap() : p(new Player()), filename_map("wmap.wmap"), load_distance(10)
{
    // link pos player with pp
    this->pp_x = &p->p_x;
    this->pp_y = &p->p_y;
    this->file_reader = new Serializer(filename_map, SERIALIZER_LOAD_MODE);
}

WorldMap::WorldMap(Player *p, std::string file, unsigned short distance) : p(p), filename_map(file), load_distance(distance)
{
    // link pos player with pp
    this->pp_x = &p->p_x;
    this->pp_y = &p->p_y;
    this->file_reader = new Serializer(filename_map, SERIALIZER_LOAD_MODE);
}

void WorldMap::load_file(Serializer &s) {
    printf("function load worldmap file is not implemented\n");
}

void WorldMap::save_file(Serializer &s) const {
    printf("function save worldmap file is not implemented\n");
}

void WorldMap::load()
{
    // load all chucnk inside distance on player

    // chunk pos player
    uint32_t cppx = *pp_x % CHUNK_WIDTH, cppy = *pp_y % CHUNK_HEIGHT;
    uint32_t start_x = cppx - load_distance, start_y = cppy - load_distance;

    for (uint32_t y = start_y; y < cppy + load_distance; y++)
    {
        for (uint32_t x = start_x; x < cppx + load_distance; x++)
        {
            Chunk c;
            load_chunk(get_id_chunk(x, y), c);
            for (auto &entity : c.entitys)
            {
                things.push_back(entity);
            }
            _map.push_back(c);
        }
    }
}

void WorldMap::save()
{
    // save all chucnk loaded
    // unload all entity
    uint64_t id;
    for (auto &ch : _map)
    {
        id = get_id_chunk(ch.p_x, ch.p_y);
        save_chunk(id, ch);
        unload_entity_chunk(id);
    }
}

/** A refaire avec la nouvelle spec de fichier */
void WorldMap::load_chunk(uint64_t id, Chunk &c)
{
    auto index = this->header.find(id);
    if (index == this->header.end())
        return;
    uint64_t offset = index->second, before = this->file_reader->where_read();
    this->file_reader->set_read(offset);
    this->file_reader->load(c);
    this->file_reader->set_read(before);
}

void WorldMap::unload_entity_chunk(uint64_t id)
{
    auto it = things.begin();
    while (it != things.end())
    {
        if (it.base()->id == id)
            things.erase(it);
    }
}

void WorldMap::save_chunk(uint64_t id, Chunk &c)
{
    if (!c.dirty)
        return;

    auto index = this->header.find(id);
    if (index == this->header.end())
        return;

    uint64_t offset = index->second, before = file_reader->where_write();

    file_reader->set_write(offset);
    file_reader->save(c);
    file_reader->set_write(before);
}

/** ------------------------------------------------------ */

void WorldMap::load_header_chunk()
{
    std::vector<id_offset> _header;
    this->file_reader->load(_header);
    for (const auto &[a, b] : _header)
    {
        this->header.emplace(a, b);
    }
}

void WorldMap::process(long double delta, uint64_t tick)
{
    for (auto e : things)
    {
        e.entity->process(delta, tick);
    }
}

void WorldMap::render(long double delta, uint64_t tick)
{
    for (auto e : things)
    {
        e.entity->render(delta, tick);
    }
}

void WorldMap::debug_print()
{
    // std::cout << "map size: " << map.size() << std::endl;
}