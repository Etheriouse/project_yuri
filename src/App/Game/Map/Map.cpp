#include "Map.hpp"
#include "App.hpp"
#include "Global.hpp"
#include <iostream>

using namespace std;

Map::Map(uint16_t w, uint16_t h) : width(w), height(h)
{
}

Map::Map(string filename, Player *p) : player(p)
{
    Serializer::Reader r(filename);
    r.read(cells);
    r.read(interactCells);
    r.read(pnjs);
    r.read(width);
    r.read(height);

    start.w = (g_app->size().w/2)-(tileSize.w/2);
    start.h = 0;
}

Map::~Map()
{
}

void Map::render(long double delta, uint64_t tick)
{
    Texture2D texture;
    /** border of draw zone, offset between two tile */
    float final_x, final_y, push = 1.2f;
    
    Size as = g_app->size();
    int binf_map_game = as.w * 0.25 + (tileSize.w / 2);
    int bsup_map_game = as.w * 0.75 - (tileSize.w / 2);

    for (uint16_t i = 0; i < height; i++)
    {
        for (uint16_t j = 0; j < width; j++)
        {
            /**
             *  Texture2D tmp;
    AppSize as = app->size();
    float final_x, final_y, push = 1.2f;
    int binf_map_game = as.width * 0.25 + (tile_width / 2);
    int bsup_map_game = as.width * 0.75 - (tile_width / 2);
    // do 0 0 at center top
    for (float y = 0; y < height; y++)
    {
        for (float x = 0; x < width; x++)
        {
            Coordinate cdp = asytoPixel({x, y});
            final_x = cdp.x * push + start_draw_x;
            final_y = cdp.y * push + start_draw_y;
            if (!(final_x + tile_width > binf_map_game && final_x < bsup_map_game))
                continue;
            if (final_y + tile_height > as.height || final_y < 0)
                continue;
            tmp = app->getTextureTile(map[y * width + x].type);
            DrawTexturePro(tmp, {0, 0, (float)tmp.width, (float)tmp.height}, {final_x, final_y, tile_width, tile_height}, {0, 0}, 0.0f, WHITE);

            DrawText((std::to_string((int)x) + ", " + std::to_string((int)y)).c_str(), (start_draw_x) * 1.2f, (cdp.y + start_draw_y) * 1.2f, 15, BLUE);
             */
            texture = g_app->TexturesGestionnary.get(cells[(i * width) + j].tile);
            Coordinate cp = asytoPixel({(float)i, (float)j}, {width, height});
            final_x = cp.x * push + start.w;
            final_y = cp.y * push + start.h;

            if (!(final_x + tileSize.w > binf_map_game && final_x < bsup_map_game))
                continue;
            if (final_y + tileSize.h > as.h || final_y < 0)
                continue;

            DrawTexturePro(texture, {0, 0, (float)texture.width, (float)texture.height}, {final_x, final_y, (float)tileSize.w, (float)tileSize.h}, {0, 0}, 0.0f, WHITE);
            

            //            cout << "(" << cells[(y * width) + x].tile << ", " << static_cast<int>(cells[(y * width) + x].flags) << ")";
        }
    }
}

void Map::process(long double delta, uint64_t tick)
{
}

void Map::debugPrint()
{
    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            cout << "(" << cells[(y * width) + x].tile << ", " << static_cast<int>(cells[(y * width) + x].flags) << ")";
        }
        cout << endl;
    }
    cout << endl;
}

void Map::iDebugPrint()
{
    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            switch (cells[(y * width) + x].tile)
            {
            case TileMap::Grass:
                cout << "# ";
                break;

            case TileMap::Stone:
                cout << "@ ";
                break;

            case TileMap::Lava:
                cout << "^ ";
                break;

            case TileMap::Water:
                cout << "~ ";
                break;

            default:
                break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Map::write(Serializer::Writer &w) const
{
    w.write(cells);
    w.write(interactCells);
    w.write(pnjs);
    w.write(width);
    w.write(height);
}

/**
 * Modify cell's map
 */
void Map::modCell(CellMap cm, size_t index)
{
    if (cells.size() <= index)
        cells.resize((cells.size() + 1) * 2);
    this->cells[index] = cm;
}

/**
 * Modify interactCell's map
 */
void Map::modInteractCell(InteractCellMap im, size_t index)
{
    if (interactCells.size() <= index)
        interactCells.resize((interactCells.size() + 1) * 2);
    this->interactCells[index] = im;
}

/**
 * Modify pnj's map
 */
void Map::modPnj(Pnj p, size_t index)
{
    if (pnjs.size() <= index)
        pnjs.resize((pnjs.size() + 1) * 2);
    this->pnjs[index] = p;
}