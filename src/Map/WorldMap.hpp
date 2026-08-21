#ifndef GAME_WORLD_MAP_HPP
#define GAME_WORLD_MAP_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <map>

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

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
    unsigned short s_layer;
    unsigned short layers;
    std::vector<WorldCell> cells;
    uint32_t p_x, p_y;
    bool dirty;
} Chunk;

typedef struct {
    uint64_t id;
    Entity *entity;
} ChunkEntity;

class WorldMap {

    public:
        WorldMap();
        WorldMap(Player *p, std::string filename_map);

        void load(Serializer& s);
        void save(Serializer& s) const;

        void load(uint64_t id, Chunk &c);
        void unload(uint64_t id);
        void save(uint64_t id, Chunk& c);
        void compact_file();

        void load_header_chunk();
        void process(long double delta, uint64_t tick);
        void render(long double delta, uint64_t tick);

        void debug_print();

    private:
        // share pos player with
        unsigned long int *pp_x, *pp_y;

        // change to chunck, load from fileglobalmap
        std::vector<WorldCell> map;
        std::map<uint64_t, uint64_t> header;

        std::string filename_map;

        Serializer *file_reader;
        std::vector<Chunk> _map;

        // entity associate to to chunk can dirty
        // todo change to vector<id_chunk, entity>
        std::vector<ChunkEntity> things;
        Player *p;

};

#endif