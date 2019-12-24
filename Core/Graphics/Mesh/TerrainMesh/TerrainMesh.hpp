#ifndef TERRAIN_MESH_HPP
#define TERRAIN_MESH_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

constexpr float half_patch_size = 0.5f;
constexpr float default_height_fix_level = 0.0f;
constexpr float default_tess_level = 49.0f;
constexpr float default_scale_level = 25.0f;

/* 
 * shader variable:
 * float : tess_level
*/
class TerrainMesh : public BaseMesh {
public:
    unsigned int mesh_width;
    unsigned int mesh_height;
    vertex_vector vertices;
    indice_vector indices;
    texture_vector textures;

    float tess_level;
    
    unsigned int VAO;
    // Width and height is the mesh size default 25.f
    // At least one height map is required
    explicit TerrainMesh(texture_vector textures,
                        imap2d &heightmap,
                        float _width = half_patch_size * 2, 
                        float _height = half_patch_size * 2);
    virtual ~TerrainMesh();

    virtual void draw(Shader const &shader) const override;
private:
    unsigned int VBO, EBO;
    virtual void setupMesh() override;
    virtual void genVertexes(imap2d &heightmap);
};

#endif