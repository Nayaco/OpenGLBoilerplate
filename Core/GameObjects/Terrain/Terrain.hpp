#ifndef TERRAIN_HPP
#define TERRIAN_HPP

#include "Core/Common.hpp"
#include "Core/Utility/Random.hpp"
#include "Core/Utility/Noise/Noise.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/TerrainMesh/TerrainMesh.hpp"


class Terrain {
public:

    enum class PLACEMENT: int {
        POSX = 0, NEGX = 1, POSZ = 2, NEGZ = 3,
    };

    TerrainMesh *terrainmesh;
    Terrain     *neighbor[4];

    imap2d terrainmap;
    int octave;
    float displaceX, displaceZ;
    float width, height;   
    float terrain_height; 
    Terrain(float _x, float _z, float _width, float _height, float _terrain_h, int octave);
    virtual ~Terrain();

    virtual void draw(Shader const &shader) const;
    virtual void setOctave(const int octave);
    virtual void setEdge(PLACEMENT exist_placement, Terrain* exist_terrain);
    virtual void generate(texture_vector const &other_textures, float tess_level);
    
    // virtual void staticGenerate(imap2d const &heightmap);
    virtual void destroy();

private:
    void processPOSX();
    void processNEGX();
    void processPOSZ();
    void processNEGZ();
    
};

#endif