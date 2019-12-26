#ifndef SKYMAP_HPP
#define SKYMAP_HPP

#include "Core/Common.hpp"
#include "Core/Context/Context.hpp"
#include "Core/Graphics/Drawable.hpp"
#include "Core/Graphics/Shader/Shader.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"
/* 
    The order of output texture is:
    0 ColorRight
    1 ColorLeft
    2 ColorUp
    3 ColorBottom
    4 ColorFront
    5 ColorBack
*/

class Skymap : public Renderable {
public:
    unsigned int    map_width;
    unsigned int    map_height;
    Shader          skymap_shader;
    texture_vector  skymap_texture;
    vertex_vector   vertices;
    glm::vec3       skymap_sun_pos;
    glm::vec3       skymap_sun_color;
    Skymap(Shader const &shader);
    virtual void initialize();
    virtual void bind();
    virtual void unbind();
    
    virtual void render() const override;
    
    virtual void update(glm::vec3 sun_pos, glm::vec3 sun_color);
    virtual void setTextureSize(unsigned int width, unsigned int height);
private:
    unsigned int FBO;
    unsigned int RBO;
    unsigned int VBO;
    unsigned int VAO;

    unsigned int attachments[6];

    virtual void setupMesh();
};

#endif