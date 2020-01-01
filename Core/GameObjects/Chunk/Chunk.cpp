#include "Chunk.hpp"

Chunk::Chunk(float x, float z, float width, float height) {
    chunk_height = height;
    chunk_width = width;
    placement_x = x;
    placement_z = z;
}
    
void Chunk::setEdge(PLACEMENT placement, Chunk* neighbor_chunk) {
}

void Chunk::setGrassMatrix(glm::mat4 projection, glm::mat4 view, glm::vec3 viewpos, glm::vec3 lightpos) {
    for (auto i = 0; i < grass.size(); i++) {
        grass[i].setProjectionMatrix(projection);
        grass[i].setViewMatrix(view);
        grass[i].setCameraPos(viewpos);
        grass[i].setLightPos(lightpos);
    }
}

void Chunk::initialize_terrain(texture_vector const &other_textures, float tess_level, float terrain_h, int octave) {
    terrain = new Terrain(placement_x, placement_z, chunk_width, chunk_height , terrain_h, octave);
    std::cout<<"terrain"<<std::endl;
    terrain->setOctave(octave);
    terrain->generate(other_textures, tess_level);
    std::cout<<"terrain"<<std::endl;
}

void Chunk::initialize_tile() {
}

void Chunk::destroy() {
}

void Chunk::draw_terrain(const Shader &terrain_shader) const {
    terrain->draw(terrain_shader);
}

void Chunk::draw_tile(const Shader &tile_shader) const {
}

void Chunk::draw_grass() {
    for (auto i = 0; i < grass.size(); i++) {
        grass[i].render();
    }
}
void Chunk::initialize_grass(const Shader &grass_shader) {
    // std::cout<<"grass"<<std::endl;
    // grassmap = noise::whiteNoise(chunk_width, chunk_height);
    // grassmap = noise::perlNoise(grassmap, 10.0, chunk_width, chunk_height);
    // float maxH = 0.0;
    // for (auto i = 0; i < chunk_width; i++) {
    //     for (auto j = 0; j < chunk_height; j++) {
    //         maxH = glm::max(maxH, grassmap[i][j]);
    //     }
    // }
    // for (auto i = 0; i < chunk_width; i++) {
    //     for (auto j = 0; j < chunk_height; j++) {
    //         grassmap[i][j] /= maxH;
    //     }
    // }
    

    grass.push_back(
        GrassBlade(glm::vec3(.1f, .6f, .1f), 
            glm::vec3(placement_x + chunk_width / 2.0, 2.5, placement_z + chunk_height / 2.0), 
            glm::vec2(chunk_width - 1.0, chunk_height - 1.0), 5.0, 
            grass_shader)
    );

    // for (auto i = 0; i < 1; i++) {
    //     for (auto j = 0; j < 1; j++) {
    //         if (grassmap[i][j] > 0.5) {
    //             std::cout<<i<<j<<std::endl;
    //             grass.push_back(
    //                 GrassBlade(
    //                     glm::vec3(0.2, 0.2, 1.0), 
    //                     glm::vec2((float)i + 0.5f + placement_x, (float)j + 0.5f + placement_z), 
    //                     glm::vec2(1.0, 1.0),
    //                     grassmap[i][j] * 8.0,
    //                     grass_shader
    //                 )
    //             );
    //             std::cout<<i<<j<<std::endl;
    //         }
    //     }
    // }
    // std::cout<<"grass"<<std::endl;
}