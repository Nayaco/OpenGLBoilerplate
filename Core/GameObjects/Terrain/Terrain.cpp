#include "Terrain.hpp"

static const float height_threshold = 0.1;
static const float height_threshold_high = 0.7;

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
            terrainmap[i][j] = _j_cb > 3 ? terrainmap[i][j] * 1.5f : terrainmap[i][j];
            terrainmap[i][j] = _j_c > 3 ? terrainmap[i][j] / 3.0f : terrainmap[i][j];
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

void Terrain::destroy() {
    delete terrainmesh;
}

void Terrain::processPOSX() {
    imap1d lerpLevel = randomx::rand(height);
    for (auto i = 0; i < height; ++i) {
        terrainmap[width - 1][i] = neighbor[(int)PLACEMENT::POSX]->terrainmap[0][i];
        lerpLevel[i] = sqrtf(lerpLevel[i]);
    }
    for (auto i = 1; i < height - 1; ++i) {
        for (auto j = 1.0f; j < (float)width / 4.0f * lerpLevel[i]; j += 1.0f) {

            float neix = (float)width / 4.0f * lerpLevel[i] + 1 - j;

            terrainmap[width - 1 - (int)j][i] = noise::lerp( 
                neighbor[(int)PLACEMENT::POSX]->terrainmap[(int)neix][i],
                terrainmap[width - 1 - (int)j][i],
                j / ((float)width / 4.0f * lerpLevel[i]));
        }
    }
}

void Terrain::processNEGX() {
    imap1d lerpLevel = randomx::rand(height);
    for (auto i = 0; i < height; ++i) {
        terrainmap[0][i] = neighbor[(int)PLACEMENT::NEGX]->terrainmap[width - 1][i];
        lerpLevel[i] = sqrtf(lerpLevel[i]);
    }
    for (auto i = 1; i < height - 1; ++i) {
        for (auto j = 1.0f; j < (float)width / 4.0f * lerpLevel[i]; j += 1.0f) {
            
            float neix = width - 2 + j - (float)width / 4.0f * lerpLevel[i];

            terrainmap[(int)j][i] = noise::lerp( 
                neighbor[(int)PLACEMENT::NEGX]->terrainmap[(int)neix][i],
                terrainmap[(int)j][i],
                j / ((float)width / 4.0f * lerpLevel[i]));
        }
    }
}

void Terrain::processPOSZ() {
    imap1d lerpLevel = randomx::rand(width);
    for (auto i = 0; i < width; ++i) {
        terrainmap[i][height - 1] = neighbor[(int)PLACEMENT::POSZ]->terrainmap[i][0];
        lerpLevel[i] = sqrtf(lerpLevel[i]);
    }
    for (auto i = 1; i < width - 1; ++i) {
        for (auto j = 1.0f; j < (float)height / 4.0f * lerpLevel[i]; j += 1.0f) {

            float neiz = (float)height / 4.0f * lerpLevel[i] + 1 - j;

            terrainmap[i][height - 1 - (int)j] = noise::lerp( 
                neighbor[(int)PLACEMENT::POSZ]->terrainmap[i][(int)neiz],
                terrainmap[i][height - 1 - (int)j],
                j / ((float)height / 4.0f * lerpLevel[i]));
        }
    }
}

void Terrain::processNEGZ() {
    imap1d lerpLevel = randomx::rand(width);
    for (auto i = 0; i < width; ++i) {
        terrainmap[i][0] = neighbor[(int)PLACEMENT::NEGX]->terrainmap[i][height - 1];
        lerpLevel[i] = sqrtf(lerpLevel[i]);
    }
    for (auto i = 1; i < width - 1; ++i) {
        for (auto j = 1.0f; j < (float)height / 4.0f * lerpLevel[i]; j += 1.0f) {
            
            float neiz = height - 2 + j - (float)height / 4.0f * lerpLevel[i];

            terrainmap[i][(int)j] = noise::lerp( 
                neighbor[(int)PLACEMENT::NEGZ]->terrainmap[i][(int)neiz],
                terrainmap[i][(int)j],
                j / ((float)height / 4.0f * lerpLevel[i]));
        }
    }
}

