#include "Chunk.hpp"

Chunk::Chunk(float x, float z, float width, float height) {

}
    
void Chunk::setEdge(PLACEMENT placement, Chunk* neighbor_chunk) {
    neighbor[(int)placement] = neighbor_chunk;
    
}


void Chunk::initialize_terrain(texture_vector const &other_textures, float tess_level, float terrain_h, int octave) {
    
}
void Chunk::initialize_tile() {

}

void Chunk::destroy() {

}

void Chunk::draw_terrain(const Shader &terrain_shader) const {

}

void Chunk::draw_tile(const Shader &tile_shader) const {

}