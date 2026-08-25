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

private:
    const std::map<TextureLocate, std::string> translate_locate_to_path = {
        {TextureLocate::Default, "default_"}};

    std::string findFolder(TextureLocate tl);

    std::map<std::string, Texture2D> loaded;
};

#endif