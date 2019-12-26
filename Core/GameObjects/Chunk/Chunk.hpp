#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/GameObjects/Terrain/Terrain.hpp"
#include "Core/GameObjects/Tile/Tile.hpp"

class Chunk {
public:
    enum class PLACEMENT: int {
        POSX = 0, NEGX = 1, POSZ = 2, NEGZ = 3,
    };

    float placement_x, placement_z;
    float chunk_width, chunk_height;
    Terrain *terrain;
    Tile    *tile;
    
    Chunk   *neighbor[4];
    
    float landHeight;
    float seaLevel;

    float grassDensity;
    
    Chunk(float x, float z, float width, float height);
    
    void setEdge(PLACEMENT placement, Chunk* neighbor_chunk);
    
    void initialize_terrain(texture_vector const &other_textures, float tess_level, float terrain_h, int octave);
    void initialize_tile();
    
    void destroy();

    void draw_terrain(const Shader &terrain_shader) const;
    void draw_tile(const Shader &tile_shader) const;
};

#endif