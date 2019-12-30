#ifndef BLOOM_HPP
#define BLOOM_HPP

#include "Core/Common.hpp"
#include "Core/PostProcessing/ScreenSpace.hpp"
#include "Core/Graphics/Texture/Texture.hpp"
#include "Core/Graphics/Mesh/BaseMesh.hpp"

class Bloom : public ScreenSpace {
    unsigned int FBO[2];
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int attachments[6];

    unsigned int width;
    unsigned int height;
    unsigned int blur_amount;
    vertex_vector   vertices;
    virtual void setupMesh();
public:
    Texture bloom_origin;
    Texture bloom_textures[2];
    unsigned int horizon;
    
    Bloom(unsigned int width, unsigned int height);
    virtual void setSize(unsigned int width, unsigned int height);
    virtual void initialize();
    virtual void bindTexture(Texture const &bloom_origin);
    virtual void draw(const Shader &shader) const override;
    virtual void bind() const override;
    virtual void unbind() const override;
};


#endif