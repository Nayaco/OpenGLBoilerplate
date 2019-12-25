#ifndef BASECAMERA_HPP
#define BASECAMERA_HPP

#include "Core/Common.hpp"

class BaseCamera {
public:
    virtual glm::mat4 GetViewMatrix() const = 0;

    virtual glm::mat4 GetProjectionMatrix() const = 0;

    virtual glm::vec3 GetViewPosition() const = 0;
};

#endif