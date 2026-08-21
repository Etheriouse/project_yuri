#ifndef GAME_SERIALIZER_HPP
#define GAME_SERIALIZER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>

#include "../Game/Entity.hpp"

constexpr uint64_t dead_chunk = 0;
constexpr uint64_t alive_chunk = UINT64_MAX;
constexpr uint64_t end_chunk = UINT64_MAX-1;

enum Serializer_mode
{
    SERIALIZER_SAVE_MODE,
    SERIALIZER_LOAD_MODE
};

typedef struct {
    uint64_t id;
    uint64_t offset;
} id_offset;

enum WorldTile {

};

// interact can dirty chunk 
typedef struct {
    WorldTile type;
    uint8_t flags; // (MSB)walk interact
} WorldCell;

typedef struct {
    unsigned short s_layer;
    unsigned short layers;
    std::vector<WorldCell> cells;
    uint32_t p_x, p_y;
    bool dirty;
} Chunk;

typedef struct {
    uint64_t id;
    Entity *entity;
} ChunkEntity;

class Serializer;

template <typename T>
concept hasLoad = requires(T &value, Serializer &s) {
    value.load(s);
};

template <typename T>
concept hasSave = requires(const T &value, Serializer &s) {
    value.save(s);
};

class Serializer
{

public:
    Serializer(std::string filename, Serializer_mode mode);
    ~Serializer();

    template <typename T>
    void load(T &n)
    {
        if constexpr (hasLoad<T>)
        {
            n.load(*this);
        }
        else if constexpr (std::is_arithmetic_v<T> || std::is_enum_v<T>)
        {
            this->read.read(reinterpret_cast<char *>(&n), sizeof(n));
        }
        else
        {
            std::cout << "For the class T as " << typeid(T).name() << std::endl;
            throw std::runtime_error("Load function not found in serializer");
        }
    }

    template <typename T>
    void load(std::vector<T> &value)
    {
        std::size_t size;

        load(size);
        value.resize(size);
        for (T &element : value)
            load(element);
    }
    template <typename T>
    void load(std::shared_ptr<T> &value)
    {
        bool exists;

        load(exists);
        if (exists)
        {
            value = std::make_shared<T>();
            load(*value);
        }
        else
            value.reset();
    }
    template <typename T>
    void load(std::unique_ptr<T> &value)
    {
        bool exists;
        load(exists);

        if (exists)
        {
            value = std::make_unique<T>();
            load(*value);
        }
        else
            value.reset();
    }

    void load(std::string &s);
    void load(WorldCell &value);
    void load(id_offset &value);
    void load(Chunk &value, std::vector<ChunkEntity> &entitys);


    template <typename T>
    void save(const T &n)
    {
        if constexpr (hasSave<T>)
        {
            n.save(*this);
        }
        else if constexpr (std::is_arithmetic_v<T> || std::is_enum_v<T>)
        {
            this->write.write(reinterpret_cast<const char *>(&n), sizeof(n));
        }
        else
        {
            std::cout << "For the class T as " << typeid(T).name() << std::endl;
            throw std::runtime_error("Save function not found in serializer");
        }
    }

    template <typename T>
    void save(const std::vector<T> &value)
    {
        std::size_t size = value.size();

        save(size);
        for (const T &element : value)
            save(element);
    }
    template <typename T>
    void save(const std::shared_ptr<T> &value)
    {
        bool exists = value != nullptr;

        save(exists);
        if (exists)
            save(*value);
    }
    template <typename T>
    void save(const std::unique_ptr<T> &value)
    {
        bool exists = value != nullptr;

        save(exists);
        if (exists)
            save(*value);
    }

    void save(const std::string &s);
    void save(const WorldCell &value);
    void save(const id_offset &value);
    void save(const Chunk &value, std::vector<ChunkEntity> &entitys);

    void set_read(uint64_t offset);
    void set_write(uint64_t offset);
    uint64_t where_read();
    uint64_t where_write();
    uint64_t end_read();
    void end_write();


private:
    const char *filename;
    std::ofstream write;
    std::ifstream read;
};

#endif