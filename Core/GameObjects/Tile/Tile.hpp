#ifndef TILE_HPP
#define TILE_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Drawable.hpp"

class Tile : public Drawable {
public:
    virtual void draw(Shader const &shader) const override;
};

#endif