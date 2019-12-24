#include "Terrain.hpp"

static const float height_threshold = 0.1;
Terrain::Terrain(float _x, float _z, float _width, float _height, float _terrain_h, int octave) {
    displaceX = _x;
    displaceZ = _z;
    width = _width;
    height = _height;
    terrain_height = _terrain_h;
    this->octave = octave;
    neighbor[0] = neighbor[1] = neighbor[2] = neighbor[3] = nullptr; 
}

Terrain::~Terrain() { }

void Terrain::draw(Shader const &shader) const {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(displaceX, 0.0f, displaceZ));
    model = glm::scale(model, glm::vec3(width, terrain_height, height));
    shader.setMat4("model", model);
    terrainmesh->draw(shader);
}

void Terrain::setEdge(PLACEMENT exist_placement, Terrain* exist_terrain) { neighbor[(int)exist_placement] = exist_terrain; }

void Terrain::setOctave(const int octave) { this->octave = octave; }

void Terrain::generate(texture_vector const &other_textures) {
    texture_vector all_textures(other_textures);
    terrainmap = noise::whiteNoise(width, height);
    terrainmap = noise::perlNoise(terrainmap, octave, width, height);
    
    for (auto i = 0; i < width; i++) {
        for (auto j = 0; j < height; j++) {
            int _j_c = 0;
            for (auto k = 0; k < 9; k++) {
                int _k_l = (k / 3) - 1;
                int _k_c = (k % 3) - 1;
                _j_c += (i + _k_l > 0) && (i + _k_l < width) && (j + _k_c > 0) && (j + _k_c < height) && terrainmap[i + _k_l][j + _k_c] < height_threshold ?
                    1 : 0;
            }
            terrainmap[i][j] = _j_c > 3 ? terrainmap[i][j] / 10 : terrainmap[i][j];
        }
    }
    
    terrainmesh = new TerrainMesh(all_textures, terrainmap, width, height);
}

void Terrain::destroy() {
    delete terrainmesh;
}
