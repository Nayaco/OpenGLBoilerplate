#ifndef BASECAMERA_HPP
#define BASECAMERA_HPP

#include "Core/Common.hpp"

class BaseCamera {
public:
    virtual glm::mat4 GetViewMatrix() const = 0;
};

#endif