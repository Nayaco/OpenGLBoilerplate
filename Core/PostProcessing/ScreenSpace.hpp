#ifndef SCREENSPACE_HPP
#define SCREENSPACE_HPP

#include "Graphics/Drawable.hpp"

class ScreenSpace : public Drawable {
public:
    virtual void draw(const Shader &shader) const = 0;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};

#endif