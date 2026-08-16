#include "Serializer.hpp"
#include <stdexcept>


Serializer::Serializer(std::string filename, unsigned int mode) {
    if(mode == SAVE_MODE) {
        this->write = std::ofstream(filename, std::ios::binary);
    } else if(mode == LOAD_MODE) {
        this->read = std::ifstream(filename, std::ios::binary);
    } else {
        throw std::invalid_argument("Invalide mode found");
    }
}

Serializer::~Serializer() {
    this->write.close();
    this->read.close();
}

void Serializer::load(std::string& value) {
    std::size_t size;
    load(size);

    value.resize(size);
    read.read(value.data(), size);
}

void Serializer::load(WorldCell& value) {
    load(value.type);
}


void Serializer::save(std::string& value) {
    std::size_t size = value.size();

    save(size);
    write.write(value.data(), size);
}

void Serializer::save(WorldCell& value) {
    save(value.type);
}