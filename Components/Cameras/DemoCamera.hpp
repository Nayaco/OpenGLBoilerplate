#ifndef DEMO_CAM
#define DEMO_CAM

#include "Core/Camera/BaseCamera.hpp"
class DemoCamera : public BaseCamera {
public:
    glm::vec3 Position = glm::vec3(0.0f, 20.0f, 100.0f);
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    float Zoom = 45.0f;
    
    virtual glm::mat4 GetViewMatrix() const override {
        return glm::lookAt(Position, Position + Front, Up);   
    }
};

#endif