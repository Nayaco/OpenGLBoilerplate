#ifndef NMP_T
#define NMP_T

#include "Core/Common.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

#include "Core/Utility/Noise/Noise.hpp"

class NPMT {
public:
    unsigned int VAO;
    unsigned int VBO, EBO;
    unsigned int mesh_width;
    unsigned int mesh_height;
    imap2d npmt;
    Texture tex;
    vertex_vector vertices;
    indice_vector indices;
    NPMT();
    void init();
    void draw(Shader const& shader) const;
    void setupMesh();
};

#endif