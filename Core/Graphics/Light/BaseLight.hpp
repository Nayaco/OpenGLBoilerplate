#ifndef BASELIGHT_HPP
#define BASELIGHT_HPP

#include "Core/Common.hpp"
#include "Core/Graphics/Shader/Shader.hpp"

class BaseLight {
public:
    virtual void light(Shader const& shader) const = 0;
};

#endif