#include "Plane.hpp"
Plane::Plane() 
    :aabbbox(glm::vec3(1.0f, 1.0f, 1.0f))
    , model("Resources/Models/Plane/plane.obj") {
    position = glm::vec3(-0.5, 9.5, -0.5);
    center = glm::vec3(0.0, 9.0, 0.0);
    vel = 6.0;
    pitch = 0;
    yaw = 0;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    aabbbox.update(position);
    calculate();
}

void Plane::ProcessKeyboard(Plane_Movement direction, float deltaTime) {
    float velocity = 60.0 * deltaTime;
    if (direction == Plane_Movement::FORWARD) {
        pitch -= velocity;
        if(pitch < -89.0) {
            pitch = -89.0;
        }
    }
    if (direction == Plane_Movement::BACKWARD) {
        pitch += velocity;
        if(pitch > 89.0) {
            pitch = 89.0;
        }  
    }
    if (direction == Plane_Movement::LEFT) {
        yaw += velocity;
    }
    if (direction == Plane_Movement::RIGHT) {
        yaw -= velocity;
    }
}

void Plane::calculate() {
    front.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}
void Plane::update(float delta_time) {
    position += front * vel * delta_time;
    center += front * vel * delta_time;
    aabbbox.update(position);
    calculate();
}

void Plane::draw(Shader const &shader) {
    glm::mat4 model_matrix(1.0);
    model_matrix = glm::translate(model_matrix, center);
    model_matrix = glm::rotate(model_matrix, glm::radians(yaw), glm::vec3(0.0, 1.0, 0.0));    
    model_matrix = glm::rotate(model_matrix, glm::radians(-pitch), glm::vec3(1.0, 0.0, 0.0));
    model_matrix = glm::scale(model_matrix, glm::vec3(0.3, 0.3, 0.3) );
    shader.use();
    shader.setMat4("model", model_matrix);
    model.draw(shader);
}