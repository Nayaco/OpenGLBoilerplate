#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Core/Common.hpp"
#include "Core/Utility/Random.hpp"
#include "Core/Utility/Noise/Noise.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"
#include "Core/Graphics/Drawable.hpp"

class Terrain : public Drawable {
public:

    enum class PLACEMENT: int {
        POSX = 0, NEGX = 1, POSZ = 2, NEGZ = 3,
    };

    TerrainMesh *terrainmesh;
    Terrain     *neighbor[4];

    imap2d terrainmap;
    int octave;
    float place_x, place_z;
    float width, height;   
    float terrain_height;
    bool reflection_refraction;

    Terrain(float _x, float _z, float _width, float _height, float _terrain_h, int octave);
    ~Terrain();

    virtual void draw(Shader const &shader) const override;
    virtual void setOctave(const int octave);
    virtual void setEdge(PLACEMENT exist_placement, Terrain* exist_terrain);
    virtual void generate(texture_vector const &other_textures, float tess_level);
    virtual void staticGenerate(imap2d const &heightmap, texture_vector const &other_textures, float tess_level);
    virtual void enableReflectionRefration();
    virtual void disableReflectionRefration();
    virtual void destroy();

private:
    virtual void processPOSX();
    virtual void processNEGX();
    virtual void processPOSZ();
    virtual void processNEGZ();
    
};

#endif