#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "Core/Graphics/Shader/Shader.hpp"

class Drawable {
public:
    virtual void draw(const Shader &shader) const = 0;
};

class Renderable {
public:
    virtual void render() const = 0;
};

#endif