#include "WorldMap.hpp"

#include "../Serializer/Serializer.hpp"
#include "../Game/Player.hpp"
#include "../Game/Entity.hpp"

WorldMap::WorldMap() : p(new Player()), filename_map("*.wmap")
{
    // link pos player with pp
    this->pp_x = &p->p_x;
    this->pp_y = &p->p_y;
}

WorldMap::WorldMap(Player *p, std::string file) : p(p), filename_map(file)
{
    // link pos player with pp
    this->pp_x = &p->p_x;
    this->pp_y = &p->p_y;
    this->file_reader = new Serializer(filename_map, SERIALIZER_LOAD_MODE);
}

void WorldMap::load(Serializer &s)
{
    s.load(map);
}

void WorldMap::save(Serializer &s) const
{
    s.save(map);
}

void WorldMap::load(uint64_t id, Chunk &c)
{
    auto index = this->header.find(id);
    if (index == this->header.end())
        return;
    uint64_t offset = index->second, before = this->file_reader->where_read();
    this->file_reader->set_read(offset);
    this->file_reader->load(c, things);
    this->file_reader->set_read(before);
}

void WorldMap::unload(uint64_t id)
{
    auto it = things.begin();
    while (it != things.end())
    {
        if (it.base()->id == id)
            things.erase(it);
    }
}

void WorldMap::save(uint64_t id, Chunk &c)
{
    if (!c.dirty)
        return;

    auto index = this->header.find(id);
    if (index == this->header.end())
        return;

    uint64_t offset = index->second, before = this->file_reader->where_write();

    // save chunk at end
    file_reader->end_write();
    file_reader->save(c, things);

    // write shit on past place
    file_reader->set_write(offset);
    file_reader->save(dead_chunk);

    this->file_reader->set_write(before);
}

void WorldMap::compact_file()
{
    std::vector<id_offset> header_;

    Serializer read(filename_map, SERIALIZER_LOAD_MODE);
    Serializer write(filename_map + ".tmp", SERIALIZER_SAVE_MODE);

    read.load(header_);
    write.save(header_);
    header_.clear();

    uint64_t isalive = 0, readed = 6498452, offset_to_write, offset_from, id = 0;
    Chunk tmp;

    while (read.where_read() < read.end_read())
    {

        offset_from = read.where_read();
        read.load(isalive);

        if (isalive == dead_chunk)
        { // read to another endchunk
            do
            {
                read.load(readed);
            } while (readed != end_chunk);
            continue;
        };

        if (isalive != alive_chunk)
            throw std::runtime_error("Invalid chunk marker");

            
        read.set_read(offset_from);
        offset_to_write = write.where_write();

        // write chunk, and get id;
        // vector is clear at each iteration
        std::vector<ChunkEntity> tmpv;
        read.load(tmp, tmpv);
        id = static_cast<uint64_t>(tmp.p_x) << 32 | static_cast<uint64_t>(tmp.p_y);
        write.save(tmp, tmpv);

        header_.emplace_back(id, offset_to_write);
    }

    write.set_write(0);
    write.save(header_);
}

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
    std::cout << "map size: " << map.size() << std::endl;
}