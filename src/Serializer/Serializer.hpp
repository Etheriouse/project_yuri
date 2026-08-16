#ifndef GAME_SERIALIZER_HPP
#define GAME_SERIALIZER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define SAVE_MODE 0
#define LOAD_MODE 1

#include "../Map/WorldMap.hpp"

class Serializer
{

public:
    Serializer(std::string filename, unsigned int mode);
    ~Serializer();

    template <typename T>
    void load(T &n)
    {
        this->read.read(reinterpret_cast<char *>(&n), sizeof(n));
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

    template <typename T>
    void save(T &n)
    {
        this->write.write(reinterpret_cast<const char *>(&n), sizeof(n));
    }
    template <typename T>
    void save(std::vector<T> &value)
    {
        std::size_t size = value.size();

        save(size);
        for (const T &element : value)
            save(element);
    }
    template <typename T>
    void save(std::shared_ptr<T> &value)
    {
        bool exists = value != nullptr;

        save(exists);
        if (exists)
            save(*value);
    }
    template <typename T>
    void save(std::unique_ptr<T> &value)
    {
        bool exists = value != nullptr;

        save(exists);
        if (exists)
            save(*value);
    }

    void save(std::string &s);
    void save(WorldCell &value);

private:
    const char *filename;
    std::ofstream write;
    std::ifstream read;
};

#endif