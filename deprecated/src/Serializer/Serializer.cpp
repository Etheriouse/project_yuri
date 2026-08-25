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

void Serializer::load(Cell &value)
{
    load(value.type);
    load(value.flags);
}

void Serializer::save(const std::string &value)
{
    std::size_t size = value.size();

    save(size);
    write.write(value.data(), size);
}

void Serializer::save(const Cell &value)
{
    save(value.type);
    save(value.flags);
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
