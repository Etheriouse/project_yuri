#include <filesystem>
#include <iostream>
using namespace std;
namespace fs = std::filesystem;

#include "TexturesGestionnary.hpp"
#include "Map.hpp"

TextureGestionnary::TextureGestionnary()
{
}

TextureGestionnary::~TextureGestionnary()
{
}

void TextureGestionnary::run()
{
    _default = LoadTexture(defaultTexturePath);
}

void TextureGestionnary::exit()
{
    UnloadTexture(_default);
    for (auto [tile, tex] : loaded)
    {
        UnloadTexture(tex);
    }
}

Texture2D TextureGestionnary::get(TileMap t)
{
    auto isLoaded = loaded.find(t);
    if (isLoaded != loaded.end())
        return isLoaded->second;

    auto isExist = translate.find(t);
    if (isExist == translate.end())
        return _default;

    cout << "TextureGestionnary: new texture loaded" << endl;

    Texture2D tex = LoadTexture(isExist->second.c_str());
    loaded.emplace(t, tex);
    return tex;
}

void TextureGestionnary::unload(TileMap tm)
{
    auto isLoaded = loaded.find(tm);
    if (isLoaded == loaded.end())
        return;
    UnloadTexture(isLoaded->second);
    loaded.erase(isLoaded);
}
