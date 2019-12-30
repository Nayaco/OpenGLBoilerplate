#ifndef FIRSTPASS_HPP
#define FIRSTPASS_HPP

#include "Core/Common.hpp"
#include "Core/ResourceManager/ResourceManager.hpp"
#include "Core/PostProcessing/ScreenSpace.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"
class FirstPass : public ScreenSpace {
    unsigned int FBO;
    unsigned int RBO;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int attachments[6];
    unsigned int width;
    unsigned int height;
    bool         bloomOn;
    float        exposure;
    vertex_vector   vertices;

    virtual void setupMesh();
public:
    enum : unsigned int{ TEX_COLOR_BUF = 0, TEX_BRIGHT_BUF = 1, TEX_DEPTH_BUF = 2};
    Texture texture_buffers[3];
    Texture texture_render[3];
    
    FirstPass(unsigned int width, unsigned int height, 
        bool bloomon, float exposure);
    virtual void initialize();
    virtual void bindTexture(Texture const &firstpass_input_texture, unsigned int texture_order);
    virtual void setSize(unsigned int width, unsigned int height);
    virtual void draw(const Shader &shader) const override;
    virtual void bind() const override;
    virtual void unbind() const override;
};
#endif