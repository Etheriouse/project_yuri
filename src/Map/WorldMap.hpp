#ifndef GAME_WORLD_MAP_HPP
#define GAME_WORLD_MAP_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <map>

constexpr uint8_t CHUNK_WIDTH = 16;
constexpr uint8_t CHUNK_HEIGHT = 16;
constexpr uint64_t dead_chunk = 0;
constexpr uint64_t alive_chunk = UINT64_MAX;
constexpr uint64_t end_chunk = UINT64_MAX-1;

class Entity;
class Player;
class Serializer;

typedef struct {
    uint64_t id;
    uint64_t offset;
} id_offset;

enum WorldTile {

};

// interact can dirty chunk 
typedef struct {
    WorldTile type;
    uint8_t flags; // (MSB)walk interact
} WorldCell;

typedef struct {
    uint64_t id;
    uint32_t pc_x, pc_y;
    Entity *entity;
} ChunkEntity;

typedef struct {
    unsigned short s_layer;
    unsigned short layers;
    std::vector<WorldCell> cells;
    std::vector<ChunkEntity> entitys;
    uint32_t p_x, p_y;
    bool dirty;
} Chunk;

class WorldMap {

    public:
        WorldMap();
        WorldMap(Player *p, std::string filename_map, unsigned short distance);

        void load();
        void save();

        void load_file(Serializer &s);
        void save_file(Serializer &s) const;

        void load_chunk(uint64_t id, Chunk &c);
        void save_chunk(uint64_t id, Chunk& c);
        void unload_entity_chunk(uint64_t id);
        
        void load_header_chunk();
        void process(long double delta, uint64_t tick);
        void render(long double delta, uint64_t tick);

        void debug_print();

        inline uint64_t get_id_chunk(uint32_t x, uint32_t y) {
            return (static_cast<uint64_t>(x) << 32) | static_cast<uint64_t>(y);
        }

    private:
        // share pos player with, value is réel coordinante, not tile coordinate
        uint32_t *pp_x, *pp_y;

        std::string filename_map;
        unsigned short load_distance;
        
        // change to chunck, load from fileglobalmap
        std::map<uint64_t, uint64_t> header;
        uint64_t offset_entity;


        Serializer *file_reader;
        std::vector<Chunk> _map;

        // entity associate to to chunk can dirty
        // todo change to vector<id_chunk, pos_of_entity_inside, entity>
        std::vector<ChunkEntity> things;
        Player *p;

};

#endif