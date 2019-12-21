#ifndef TERRAIN_MESH_HPP
#define TERRAIN_MESH_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "BaseMesh.hpp"

constexpr float half_patch_size = 25.0f;

// !IMPORTANT TerrainMesh should include Tess-cs and Tess-es shaders 
class TerrainMesh : public BaseMesh {
public:
    unsigned int mesh_width;
    unsigned int mesh_height;
    vertex_vector vertices;
    indice_vector indices;
    texture_vector textures;
    unsigned int VAO;
// Width and height is the mesh size default 25.f
// At least one height map is required
    explicit TerrainMesh(texture_vector textures, 
                        unsigned int _width = half_patch_size * 2, 
                        unsigned int _height = half_patch_size * 2);
    virtual void Draw(Shader const &shader) const override;
private:
    unsigned int VBO, EBO;
    virtual void setupMesh() override;
};

#endif