#ifndef BILLBOARD_HPP
#define BILLBOARD_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

class BillBoard : public Drawable {
    unsigned int VAO;
    unsigned int VBO, EBO;
    glm::vec3    entity_sunpos;
    glm::vec3    entity_suncolor;
    glm::mat4    entity_model;
    vertex_vector  vertices;
    indice_vector  indices;
public:
    virtual void draw(const Shader &shader) const override;
};

#endif