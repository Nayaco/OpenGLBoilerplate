#ifndef CAMERA_H
#define CAMERA_H

#include "BaseCamera.hpp"
#include "Core/Context/Context.hpp"

const float DEFAULT_YAW         = -90.0f;
const float DEFAULT_PITCH       =  0.0f;
const float DEFAULT_SPEED       =  6.0f;
const float DEFAULT_SENSITIVITY =  0.1f;
const float DEFAULT_ZOOM        =  45.0f;
const float DEFAULT_FAR         =  1000.0f;
const float DEFAULT_NEAR        =  0.1f;

// Eular Camera

class Camera : public BaseCamera {
public:
    enum class Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
    };
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float Far;
    float Near;
    bool  reflect;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
            float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH, float far = DEFAULT_FAR, float near = DEFAULT_NEAR);

    Camera(float posX, float posY, float posZ, 
            float upX, float upY, float upZ, 
            float yaw, float pitch,
            float far, float near);
    virtual ~Camera(); 
    virtual glm::mat4 GetViewMatrix() const override;
    virtual glm::mat4 GetProjectionMatrix() const override;
    virtual glm::vec3 GetViewPosition() const override;
    virtual glm::vec2 GetNearFar() const;
    virtual void Reflect(float height);
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    void updateCameraVectors();
};
#endif