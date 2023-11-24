#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

enum CAMERA_MOVEMENT
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const glm::vec3 POSITION = glm::vec3(0.0f, 2.0f, 2.0f);
const float YAW = -90.0f;
const float PITCH = -25.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class CameraObject
{
private:
    glm::vec3 position, front, up, right, worldUp;
    float speed, yaw, pitch, mouseSensitivity, zoom;

    void updateCameraVectors();

public:
    CameraObject(
        glm::vec3 _position = POSITION,
        glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
        float _yaw = YAW,
        float _pitch = PITCH);

    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition() { return position; };
    glm::vec3 GetFront() { return front; };
    void ProcessInput(CAMERA_MOVEMENT direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    ~CameraObject();
};