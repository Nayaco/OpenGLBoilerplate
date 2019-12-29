#ifndef ENTITYSUN_HPP
#define ENTITYSUN_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

class EntitySun : public Drawable {
    unsigned int VAO;
    unsigned int VBO, EBO;
    glm::vec3    entity_sunpos;
    glm::vec3    entity_suncolor;
    glm::mat4    entity_model;
    vertex_vector  vertices;
    indice_vector  indices;

    virtual void setupMesh();
    virtual void genSphere(vertex_vector &_vertices, indice_vector &_indices,
                glm::vec3 center, float radius, int division);
public:
    EntitySun();
    virtual void draw(const Shader &shader) const override;
    virtual void update(glm::vec3 sunpos, glm::vec3 suncolor);
};

#endif