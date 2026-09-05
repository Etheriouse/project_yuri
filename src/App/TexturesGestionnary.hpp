#ifndef APP_TEXTURE_GESTIONNARY_HPP
#define APP_TEXTURE_GESTIONNARY_HPP

#include <map>
#include <string>
#include <raylib.h>
#include "Map.hpp"

class TextureGestionnary
{

public:
    TextureGestionnary();
    ~TextureGestionnary();

    /**
     * Preapare and setup the texture gesionnary after the initilization of the opengl context
     * @note this function need to be call AFTER InitWindow
     */
    void run();

     /**
     * Unload all texture loaded before closing the window
     * @note this function need to be call BEFORE CloseWindow
     */
    void exit();

    /**
     * Get a texture from a tilemap
     * @param tm a tilemap
     */
    Texture2D get(TileMap tm);

    /**
     * Unload texture from a tilemap
     * @param tm a tilemap
     */
    void unload(TileMap tm);

private:
    const char * defaultTexturePath = "assets/default/default.png";
    Texture2D _default;

    std::map<TileMap, Texture2D> loaded;
    const std::map<TileMap, std::string> translate = {};
};

#endif