#include <filesystem>
namespace fs = std::filesystem;

#include "TexturesGestionnary.hpp"

TextureGestionnary::TextureGestionnary()
{
}

std::string TextureGestionnary::findFolder(TextureLocate tl)
{
    auto it = translate_locate_to_path.find(tl);
    if (it == translate_locate_to_path.end())
        return translate_locate_to_path.at(TextureLocate::Default);
    else
        return it->second;
}

void TextureGestionnary::load(TextureLocate who)
{
    fs::path folder = findFolder(who);

    for (const auto &entry : fs::directory_iterator(folder))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path();
            loaded[filename] = LoadTexture(filename.c_str());
        }
    }
}

void TextureGestionnary::unload(TextureLocate who)
{
    std::string folder = findFolder(who);
    
    auto it = loaded.begin();
    while(it != loaded.end()) {
        if(it->first.rfind(folder, 0) != std::string::npos) {
            UnloadTexture(it->second);
            it = loaded.erase(it);
        } else {
            it++;
        }
    }
}

void TextureGestionnary::unloadAll()
{
    for (auto [name, tx] : loaded)
    {
        UnloadTexture(tx);
    }
    loaded.clear();
}