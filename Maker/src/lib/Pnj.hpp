#ifndef GAME_PNJ_HPP
#define GAME_PNJ_HPP

#include <fstream>
#include <string>

class Pnj {

    public:
        void save(std::ofstream& file) {
            size_t textureSize = texture.size();
            size_t nameSize = name.size();
            file.write(reinterpret_cast<const char*>(textureSize), sizeof(textureSize));
            file.write(texture.data(), textureSize);
            file.write(reinterpret_cast<const char*>(nameSize), sizeof(nameSize));
            file.write(name.data(), nameSize);
            file.write(reinterpret_cast<const char*>(x), sizeof(x));
            file.write(reinterpret_cast<const char*>(y), sizeof(y));
            file.write(reinterpret_cast<const char*>(uidDialogue), sizeof(uidDialogue));
        }

    private:
        uint64_t uidDialogue;
        std::string texture, name;
        uint16_t x, y;
};

#endif