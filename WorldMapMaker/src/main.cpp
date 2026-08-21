#include "Serializer/Serializer.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "bitmapl.hpp"

using namespace std;
using namespace bmp;

/**
 * argv, width, height, folder, result
 */
int main(int argc, char const *argv[])
{
    if(argc != 5) { cerr << "invalide argument number" << endl; return -1;}
    const short CHUNK_WIDTH = stoi(argv[1]), CHUNK_HEIGHT = stoi(argv[2]);
    string filename = argv[4];
    filename+=".wmap";
    vector<Bitmap> layers;


    for (const auto &entry : filesystem::directory_iterator(argv[3]))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".bmp")
        {
            Bitmap img((entry.path().c_str()));
            layers.push_back(img);
        }
    }

    Serializer s(filename, SERIALIZER_SAVE_MODE);

    uint32_t g_width = layers[0].width(), g_height = layers[0].height();

    cout << g_height << endl;

    for (uint32_t i = 0; i < g_height; i += CHUNK_HEIGHT)
    {
        for (uint32_t j = 0; j < g_width; j += CHUNK_WIDTH)
        {
            Chunk c;
            for(size_t z = 0; z<layers.size(); z++) {
                for(int y = 0; y<CHUNK_HEIGHT; y++) {
                    for(int x = 0; x<CHUNK_WIDTH; x++) {
                        Pixel p = layers[z].get(y+i, x+j);
                        cout << "r" << p.r << " g " << p.g << " b " << p.b << endl;
                    }
                }
            }
        }
    }

    return 0;
}
