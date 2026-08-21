#include "Serializer.hpp"
#include "../Game/Mob.hpp"
#include "../Game/Player.hpp"
#include <stdexcept>

Serializer::Serializer(std::string filename, Serializer_mode mode)
{
    if (mode == SERIALIZER_SAVE_MODE)
    {
        this->write = std::ofstream(filename, std::ios::binary);
    }
    else if (mode == SERIALIZER_LOAD_MODE)
    {
        this->read = std::ifstream(filename, std::ios::binary);
    }
    else
    {
        throw std::invalid_argument("Invalide mode found");
    }
}

Serializer::~Serializer()
{
    this->write.close();
    this->read.close();
}

void Serializer::load(std::string &value)
{
    std::size_t size;
    load(size);

    value.resize(size);
    read.read(value.data(), size);
}

void Serializer::load(WorldCell &value)
{
    load(value.type);
    load(value.flags);
}

void Serializer::load(id_offset &value)
{
    load(value.id);
    load(value.offset);
}

void Serializer::load(Chunk &value, std::vector<ChunkEntity> &entitys)
{
    uint64_t id = (static_cast<uint64_t>(value.p_x) << 32) | static_cast<uint64_t>(value.p_y);

    uint64_t alive = 0, end_c;
    load(alive);
    load(value.layers);
    load(value.s_layer);
    load(value.p_x);
    load(value.p_y);
    load(value.dirty);
    load(value.cells);
    size_t nb_entitys = 0;
    TypeEntity type;
    std::unique_ptr<Entity> entity;
    load(nb_entitys);
    for (size_t i = 0; i < nb_entitys; i++)
    {
        load(type);
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
    }
    load(*entity);
    entitys.push_back({id, entity.get()});
    load(end_c);
}

void Serializer::save(const std::string &value)
{
    std::size_t size = value.size();

    save(size);
    write.write(value.data(), size);
}

void Serializer::save(const WorldCell &value)
{
    save(value.type);
    save(value.flags);
}

void Serializer::save(const id_offset &value)
{
    save(value.id);
    save(value.offset);
}

void Serializer::save(const Chunk &value, std::vector<ChunkEntity> &entitys)
{
    uint64_t id = (static_cast<uint64_t>(value.p_x) << 32) | static_cast<uint64_t>(value.p_y);

    std::vector<Entity *> in_chunk;
    for (const auto &[_id, e] : entitys)
    {
        if (id == _id)
            in_chunk.push_back(e);
    }

    save(alive_chunk);
    save(value.layers);
    save(value.s_layer);
    save(value.p_x);
    save(value.p_y);
    save(value.dirty);
    save(value.cells);
    save(in_chunk.size());
    for (Entity *e : in_chunk)
    {
        save(e->type());
        save(*e);
    }
    save(end_chunk);
}

void Serializer::set_read(uint64_t offset)
{
    read.seekg(
        static_cast<std::streamoff>(offset),
        std::ios::beg);
}

uint64_t Serializer::where_read()
{
    return static_cast<uint64_t>(read.tellg());
}

void Serializer::set_write(uint64_t offset)
{
    write.seekp(
        static_cast<std::streamoff>(offset),
        std::ios::beg);
}

uint64_t Serializer::where_write()
{
    return static_cast<uint64_t>(write.tellp());
}

/**
 * Tell where is end file for read
 */
uint64_t Serializer::end_read() {
   return read.end;
}

/**
 * Go to end file for write
 */
void Serializer::end_write()
{
    write.seekp(0, std::ios::end);
}

