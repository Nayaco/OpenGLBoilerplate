#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float far, float near)
    :Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
    MovementSpeed(DEFAULT_SPEED), MouseSensitivity(DEFAULT_SENSITIVITY), Zoom(DEFAULT_ZOOM) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Far = far;
        Near = near;
        reflect = false;
        updateCameraVectors();
}
    
Camera::Camera(float posX, float posY, float posZ, 
            float upX, float upY, float upZ, 
            float yaw, float pitch,
            float far, float near) 
    :Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
    MovementSpeed(DEFAULT_SPEED), MouseSensitivity(DEFAULT_SENSITIVITY), Zoom(DEFAULT_ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    Far = far;
    Near = near;
    reflect = false;
    updateCameraVectors();
}

Camera::~Camera() { }

glm::mat4 Camera::GetProjectionMatrix() const { return glm::perspective(glm::radians(Zoom), (float)Context::window_width / (float)Context::window_height, Near, Far); }

glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(Position, Position + Front, Up); }

glm::vec3 Camera::GetViewPosition() const { return Position; }

glm::vec2 Camera::GetNearFar() const { return glm::vec2(Near, Far); }

void Camera::Reflect(float height) {
    reflect = !reflect;
    Position.y = 2 * height - Position.y;
    updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        Position += Front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        Position -= Front * velocity;
    if (direction == Camera_Movement::LEFT)
        Position -= Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw   += xoffset;
    Pitch += yoffset;
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f) Zoom -= yoffset;
    if (Zoom <= 1.0f) Zoom = 1.0f;
    if (Zoom >= 45.0f) Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
     if (!reflect) {
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    } else {
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(-Pitch));
        front.y = sin(glm::radians(-Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(-Pitch));
    }
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}