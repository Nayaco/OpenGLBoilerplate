#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

class Skybox {
    unsigned int VAO;
    unsigned int VBO, EBO;
    virtual void setupMesh();
public:
    vertex_vector  vertices;
    indice_vector  indices;
    Texture        texture;
    texture_vector skybox_textures;
    Shader         skybox_shader;
    glm::vec3      sky_color;
    bool           use_cube_map;
    
    Texture        cloud_textrue;
    
    // Skybox(Texture texture, Shader const& shader);
    Skybox(texture_vector cube, Shader const& shader);
    virtual ~Skybox();
    virtual void setColor(glm::vec3 color);
    // virtual void draw(Shader const &shader) const;
    virtual void draw() const;
    virtual void update(texture_vector cube);
    virtual void bindCloud(Texture const &_cloud_texture);
    virtual void setPV(glm::mat4 const &projection, glm::mat4 const &view);    
};

#endif