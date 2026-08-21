#include "Serializer/Serializer.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define AIR 78990

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Layer
{
    uint32_t width;
    uint32_t height;
    std::vector<Pixel> pixels;
};

using namespace std;

Layer loadImage(const char *filename)
{
    int width, height, channels;

    std::cout << "Loading: " << filename << '\n';

    unsigned char *data = stbi_load(
        filename,
        &width,
        &height,
        &channels,
        3);

    if (!data)
    {
        std::cerr << "STB ERROR: "
                  << stbi_failure_reason()
                  << '\n';

        return {};
    }

    std::cout << "OK: "
              << width << "x" << height
              << " channels=" << channels
              << '\n';

    Layer layer;
    layer.width = width;
    layer.height = height;
    layer.pixels.resize(static_cast<size_t>(width) * height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            size_t i = (static_cast<size_t>(y) * width + x) * 3;

            layer.pixels[y * width + x] = {
                data[i],
                data[i + 1],
                data[i + 2]};
        }
    }

    stbi_image_free(data);

    return layer;
}

// rgb color
// xxxxxxxx 00000000 0000 0000 00000000
// 12 lsb = tile
// 12-16 = ???
// 16-24 = flags

WorldCell get_world_cell(uint16_t tile, uint8_t flags)
{
    WorldTile t;
    switch (tile)
    {
    case AIR:
        t = WorldTile::Air;
        break;

    default:
        t = WorldTile::Void;
        break;
    }
    return {t, flags};
}

/**
 * argv, width, height, folder, result
 */
int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        cerr << "invalide argument number" << endl;
        return -1;
    }
    const short CHUNK_WIDTH = stoi(argv[1]), CHUNK_HEIGHT = stoi(argv[2]);
    string filename = argv[4];
    filename += ".wmap";
    vector<Layer> layers;
    uint32_t g_width, g_height;

    for (const auto &entry : filesystem::directory_iterator(argv[3]))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".png")
        {
            cout << entry.path().c_str() << endl;
            layers.push_back(loadImage(entry.path().c_str()));
        }
    }

    g_width = layers[0].width;
    g_height = layers[0].height;
    Serializer s(filename, SERIALIZER_SAVE_MODE);

    vector<Chunk> map;

    for (uint32_t i = 0; i < g_height; i += CHUNK_HEIGHT)
    {
        for (uint32_t j = 0; j < g_width; j += CHUNK_WIDTH)
        {
            Chunk c;
            for (size_t z = 0; z < layers.size(); z++)
            {
                for (int y = 0; y < CHUNK_HEIGHT; y++)
                {
                    for (int x = 0; x < CHUNK_WIDTH; x++)
                    {
                        Pixel p = layers[z].pixels[((y + i) * g_height) + x + j];
                        uint32_t color = static_cast<uint32_t>(p.r << 16) | static_cast<uint32_t>(p.g << 8) | static_cast<uint32_t>(p.b);
                        c.cells.push_back(get_world_cell(static_cast<uint16_t>(color & 0x0FFF), color >> 16));
                    }
                }
            }
            map.push_back(c);
        }
    }

    for (int i = 0; i < g_height / CHUNK_HEIGHT; i++)
    {
        for (int j = 0; j < g_width / CHUNK_WIDTH; j++)
        {
            for (int k = 0; k < CHUNK_HEIGHT; k++)
            {
                for (int l = 0; l < CHUNK_WIDTH; l++)
                {
                    switch (map[i * (g_width / CHUNK_WIDTH) + j].cells[k * CHUNK_WIDTH + l].type)
                    {
                    case WorldTile::Wall:
                        cout << " # ";
                        break;
                    case WorldTile::Air:
                        cout << "   ";
                        break;

                    default:
                        cout << " ? ";
                        break;
                    }
                }
                cout << endl;
            }
        }
    }

    return 0;
}
