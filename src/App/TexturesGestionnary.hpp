#ifndef APP_TEXTURE_GESTIONNARY_HPP
#define APP_TEXTURE_GESTIONNARY_HPP

#include <map>
#include <string>
#include <raylib.h>

enum TextureLocate
{
    Default
};

class TextureGestionnary
{

public:
    TextureGestionnary();

    /**
     * Load all the texture who is in the location 'who'
     * @param who a location
     */
    void load(TextureLocate who);

    /**
     * Unload all the texture who is in the location 'who'
     * @param who a location
     */
    void unload(TextureLocate who);

    /**
     * Unload all the texture loaded
     */
    void unloadAll();

    /**
     * Get a Texture2D from a tile
     */
    Texture2D get(TileMap t);

private:
    const std::map<TextureLocate, std::string> translate_locate_to_path = {
        {TextureLocate::Default, "default_"}};

    const std::map<TileMap, std::string> texture2d_from_tilemap = {
        {TileMap::Default, "default_/default.png"}};

    std::string findFolder(TextureLocate tl);

    std::map<std::string, Texture2D> loaded;
};

#endif