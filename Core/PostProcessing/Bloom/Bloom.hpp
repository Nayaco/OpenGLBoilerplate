#ifndef BLOOM_HPP
#define BLOOM_HPP

#include "Core/Common.hpp"
#include "Core/PostProcessing/ScreenSpace.hpp"

class Bloom : public ScreenSpace {
    unsigned int EBO;
    unsigned int VBO;
public:
    virtual void draw(const Shader &shader) const override;
    virtual void bind() const override;
    virtual void unbind() const override;
};


#endif