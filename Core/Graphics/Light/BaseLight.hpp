#ifndef BASELIGHT_HPP
#define BASELIGHT_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

class BaseLight {
public:
    virtual void use(Shader const& shader) const = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
};

#endif