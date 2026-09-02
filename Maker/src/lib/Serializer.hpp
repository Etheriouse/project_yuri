#ifndef APP_SERIALIZER_HPP
#define APP_SERIALIZER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <concepts>

namespace Serializer
{
    class Writer;

    template <typename T>
    concept WriteSerializable = requires(const T element, Serializer::Writer &serializer) {
        { element.write(serializer) } -> std::same_as<void>;
    };

     template <typename T>
    concept IsPrimitif = std::is_arithmetic_v<T> || std::is_enum_v<T>;// || std::_Is_character_or_bool<T>;

    class Writer
    {

    public:
        Writer(std::string filename)
        {
            file = std::ofstream(filename, std::ios::binary);
        }

        template <WriteSerializable T>
        void write(const T &element)
        {
            element.write(*this);
        }

        template <typename T>
        void write(const std::vector<T> &vector)
        {
            write(vector.size());
            for (const auto &e : vector) write(e);
        }

        void write(const std::string &element)
        {
            write(element.size());
            file.write(element.data(), element.size());
        }

        template <IsPrimitif T>
        void write(const T& element)
        {
            file.write(reinterpret_cast<const char *>(&element), sizeof(element));
        }

    private:
        std::ofstream file;
    };

    class Reader
    {

    public:
        Reader(std::string filename);

    private:
        std::ifstream file;
    };
}

#endif