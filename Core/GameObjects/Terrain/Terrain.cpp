#include "Terrain.hpp"

static const float height_threshold = 0.1;
static const float height_threshold_high = 0.4;
static const int   perl1d_level = 4;
Terrain::Terrain(float _x, float _z, float _width, float _height, float _terrain_h, int octave) : terrainmap(_width) {
    place_x = _x;
    place_z = _z;
    width = _width;
    height = _height;
    terrain_height = _terrain_h;
    this->octave = octave;
    neighbor[0] = neighbor[1] = neighbor[2] = neighbor[3] = nullptr; 
}

Terrain::~Terrain() { }

void Terrain::draw(Shader const &shader) const {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(place_x, 0.0f, place_z));
    model = glm::scale(model, glm::vec3(width, terrain_height, height));
    shader.setMat4("model", model);
    terrainmesh->draw(shader);
}

void Terrain::setEdge(PLACEMENT exist_placement, Terrain* exist_terrain) { neighbor[(int)exist_placement] = exist_terrain; }

void Terrain::setOctave(const int octave) { this->octave = octave; }

void Terrain::generate(texture_vector const &other_textures, float tess_level) {
    texture_vector all_textures(other_textures);
    terrainmap = noise::whiteNoise(width, height);
    terrainmap = noise::perlNoise(terrainmap, octave, width, height);
    
    for (auto i = 0; i < width; i++) {
        for (auto j = 0; j < height; j++) {
            int _j_c = 0;
            int _j_cb = 0;
            for (auto k = 0; k < 9; k++) {
                int _k_l = (k / 3) - 1;
                int _k_c = (k % 3) - 1;
                _j_c += (i + _k_l > 0) && (i + _k_l < width) && (j + _k_c > 0) && (j + _k_c < height) && terrainmap[i + _k_l][j + _k_c] < height_threshold ?
                    1 : 0;
                _j_cb += (i + _k_l > 0) && (i + _k_l < width) && (j + _k_c > 0) && (j + _k_c < height) && terrainmap[i + _k_l][j + _k_c] > height_threshold_high ?
                    1 : 0;
            }
            terrainmap[i][j] = _j_cb > 3 && terrainmap[i][j] < 0.65 && i != 0 && j != 0 && i != width - 1 && j != height - 1 ? 
                terrainmap[i][j] * 1.5f : terrainmap[i][j];
            terrainmap[i][j] = _j_c > 3 ? terrainmap[i][j] / 1.5f : terrainmap[i][j];
        }
    }
    for (auto i = 0; i < width; i++) {
            for (auto j = 0; j < height; j++) {
                if(i == 0 && j != 0) {
                    terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i + 1][j] * 0.8;
                }
                if(i == width && j != height) {
                    terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i - 1][j] * 0.8;
                }
                if(j == 0 && i != width) {
                    terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i][j + 1] * 0.8;
                }
                if(j == height && i!= 0) {
                    terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i][j - 1] * 0.8;
                }
            }
        }
    if (neighbor[(int)PLACEMENT::POSX] != nullptr)
        processPOSX();
    if (neighbor[(int)PLACEMENT::NEGX] != nullptr)
        processNEGX();
    if (neighbor[(int)PLACEMENT::POSZ] != nullptr)
        processPOSZ();
    if (neighbor[(int)PLACEMENT::NEGZ] != nullptr)
        processNEGZ();
    
    terrainmesh = new TerrainMesh(all_textures, terrainmap, width, height, tess_level);
}

void Terrain::staticGenerate(imap2d const &heightmap, texture_vector const &other_textures, float tess_level) {
    texture_vector all_textures(other_textures);
    auto static_width = heightmap.size();
    auto static_height = heightmap[0].size();
    
    for (auto i = 0; i < width; i++) {
        for (auto j = 0; j < height; j++) {
            float u = (float)i / (float)width;
            float v = (float)j / (float)height;
            float static_i = u * static_width;
            float static_j = v * static_height;
            float left = floor(static_i);
            float right= ceil(static_i);
            float down = floor(static_j);
            float top  = ceil(static_j);
            right = right > static_width - 1 ? static_width - 1 : right;
            top = top > static_height - 1 ? static_height - 1 : top; 
            float horizon_up = noise::lerp(heightmap[(int)left][(int)top], heightmap[(int)left][(int)top], static_i - left);
            float horizon_down = noise::lerp(heightmap[(int)left][(int)down], heightmap[(int)left][(int)down], static_i - left);
            
            float vertical = noise::lerp(horizon_down, horizon_up, static_j - down);
            terrainmap[i].push_back(vertical);
        }
    }
    
    // for (auto i = 0; i < width; i++) {
    //     for (auto j = 0; j < height; j++) {
    //         int _j_c = 0;
    //         int _j_cb = 0;
    //         for (auto k = 0; k < 9; k++) {
    //             int _k_l = (k / 3) - 1;
    //             int _k_c = (k % 3) - 1;
    //             _j_c += (i + _k_l > 0) && (i + _k_l < width) && (j + _k_c > 0) && (j + _k_c < height) && terrainmap[i + _k_l][j + _k_c] < height_threshold ?
    //                 1 : 0;
    //             _j_cb += (i + _k_l > 0) && (i + _k_l < width) && (j + _k_c > 0) && (j + _k_c < height) && terrainmap[i + _k_l][j + _k_c] > height_threshold_high ?
    //                 1 : 0;
    //         }
    //         terrainmap[i][j] = _j_cb > 3 && terrainmap[i][j] < 0.65 && i != 0 && j != 0 && i != width - 1 && j != height - 1 ? 
    //             terrainmap[i][j] * 1.5f : terrainmap[i][j];
    //         terrainmap[i][j] = _j_c > 3 ? terrainmap[i][j] / 3.0f : terrainmap[i][j];
    //     }
    // }

    for (auto i = 0; i < width; i++) {
        for (auto j = 0; j < height; j++) {
            if(i == 0 && j != 0) {
                terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i + 1][j] * 0.8;
            }
            if(i == width && j != height) {
                terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i - 1][j] * 0.8;
            }
            if(j == 0 && i != width) {
                terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i][j + 1] * 0.8;
            }
            if(j == height && i!= 0) {
                terrainmap[i][j] = terrainmap[i][j] * 0.2 + terrainmap[i][j - 1] * 0.8;
            }
        }
    }

    
    terrainmesh = new TerrainMesh(all_textures, terrainmap, width, height, tess_level);
}

void Terrain::destroy() {
    delete terrainmesh;
}

void Terrain::processPOSX() {
    imap1d lerp_level = noise::perlNoise1d(randomx::rand(height), perl1d_level, height);
    for (auto i = 0; i < height; ++i) {
        terrainmap[width - 1][i] = neighbor[(int)PLACEMENT::POSX]->terrainmap[0][i];
    }
    for (auto i = 1; i < height; ++i) {
        for (auto j = 1.0f; j < (float)width / 4.0f * lerp_level[i]; j += 1.0f) {
            float neix = (float)width / 4.0f * lerp_level[i] + 1 - j;

            terrainmap[width - 1 - (int)j][i] = noise::lerp( 
                neighbor[(int)PLACEMENT::POSX]->terrainmap[(int)neix][i],
                terrainmap[width - 1 - (int)j][i],
                j / ((float)width / 4.0f * lerp_level[i]));
        }
    }
}

void Terrain::processNEGX() {
    imap1d lerp_level = noise::perlNoise1d(randomx::rand(height), perl1d_level, height);
    for (auto i = 0; i < height; ++i) {
        terrainmap[0][i] = neighbor[(int)PLACEMENT::NEGX]->terrainmap[width - 1][i];
    }
    for (auto i = 1; i < height - 1; ++i) {
        for (auto j = 1.0f; j < (float)width / 4.0f * lerp_level[i]; j += 1.0f) {
            float neix = width - 2 + j - (float)width / 4.0f * lerp_level[i];

            terrainmap[(int)j][i] = noise::lerp( 
                neighbor[(int)PLACEMENT::NEGX]->terrainmap[(int)neix][i],
                terrainmap[(int)j][i],
                j / ((float)width / 4.0f * lerp_level[i]));
        }
    }
}

void Terrain::processPOSZ() {
    imap1d lerp_level = noise::perlNoise1d(randomx::rand(width), perl1d_level, width);
    for (auto i = 0; i < width; ++i) {
        terrainmap[i][height - 1] = neighbor[(int)PLACEMENT::POSZ]->terrainmap[i][0];
    }
    for (auto i = 1; i < width - 1; ++i) {
        for (auto j = 1.0f; j < (float)height / 4.0f * lerp_level[i]; j += 1.0f) {
            float neiz = j + (float)height / 4.0f * lerp_level[i]; 

            terrainmap[i][height - 1 - (int)j] = noise::lerp( 
                neighbor[(int)PLACEMENT::POSZ]->terrainmap[i][(int)neiz],
                terrainmap[i][height - 1 - (int)j],
                j / ((float)width / 4.0f * lerp_level[i]));
        }
    }
}

void Terrain::processNEGZ() {
    imap1d lerp_level = noise::perlNoise1d(randomx::rand(width), perl1d_level, width);
    for (auto i = 0; i < width; ++i) {
        terrainmap[i][0] = neighbor[(int)PLACEMENT::NEGX]->terrainmap[i][height - 1];
    }
    for (auto i = 1; i < width - 1; ++i) {
        for (auto j = 1.0f; j < (float)height / 4.0f * lerp_level[i]; j += 1.0f) {
            float neiz = height - 2 + j - (float)height / 4.0f * lerp_level[i];

            terrainmap[i][(int)j] = noise::lerp( 
                neighbor[(int)PLACEMENT::NEGZ]->terrainmap[i][(int)neiz],
                terrainmap[i][(int)j],
                j / ((float)width / 4.0f * lerp_level[i]));
        }
    }

}

