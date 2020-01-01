#ifndef PLANE_HPP
#define PLANE_HPP

#include "Core/Common.hpp"
#include "Core/Physics/AABB/AABBObject.hpp"
#include "Core/Graphics/Model/Model.hpp"
struct Plane {
    enum class Plane_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
    };
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 worldUp;
    glm::vec3 right;
    float vel;
    
    float pitch;
    float yaw;
    AABBObject aabbbox;
    Model model;
    Plane();
    
    void ProcessKeyboard(Plane_Movement direction, float deltaTime);

    void update(float delta_time);
    void draw(Shader const &shader); 
    void calculate();
};

#endif