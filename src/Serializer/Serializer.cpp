#include "Serializer.hpp"
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

void Serializer::load(Cell &value)
{
    load(value.type);
    load(value.texture);
}

void Serializer::load(id_offset &value)
{
    load(value.id);
    load(value.offset);
}

void Serializer::load(Chunk &value)
{
    load(value.layers);
    load(value.s_layer);
    load(value.p_x);
    load(value.p_y);
    load(value.dirty);
    load(value.cells);
    load(value.entitys);
}

void Serializer::load(ChunkEntity &value)
{
    load(value.id);
    load(value.pc_x);
    load(value.pc_y);
    TypeEntity type;
    std::unique_ptr<Entity> entity;
    load(type);
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
    load(*entity);
    value.entity = entity.get();
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

void Serializer::save(const Cell &value)
{
    save(value.type);
    save(value.texture);
}

void Serializer::save(const id_offset &value)
{
    save(value.id);
    save(value.offset);
}

void Serializer::save(const Chunk &value)
{
    save(value.layers);
    save(value.s_layer);
    save(value.p_x);
    save(value.p_y);
    save(value.dirty);
    save(value.cells);
    save(value.entitys);
}

void Serializer::save(const ChunkEntity &value)
{
    save(value.id);
    save(value.pc_x);
    save(value.pc_y);
    save(value.entity->type());
    save(*value.entity);
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
uint64_t Serializer::end_read()
{
    return read.end;
}

/**
 * Go to end file for write
 */
void Serializer::end_write()
{
    write.seekp(0, std::ios::end);
}
