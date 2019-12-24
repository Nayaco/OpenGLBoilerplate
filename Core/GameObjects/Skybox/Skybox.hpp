#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

class Skybox : public BaseMesh {
public:
    vertex_vector vertices;
    indice_vector indices;
    Texture       texture;
    unsigned int VAO;
    glm::vec3 sky_color;
    
    Skybox(Texture texture);
    virtual ~Skybox();
    virtual void setColor(glm::vec3 color);
    virtual void draw(Shader const &shader) const override;
private:
    unsigned int VBO, EBO;
    virtual void setupMesh() override;
};

#endif