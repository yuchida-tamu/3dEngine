#include "camera.h"

CameraObject::CameraObject(glm::vec3 _position,
                           glm::vec3 _up,
                           float _yaw,
                           float _pitch)
{
    position = _position;
    worldUp = _up;
    yaw = _yaw;
    pitch = _pitch;
    speed = SPEED;
    mouseSensitivity = SENSITIVITY;

    updateCameraVectors();
}

void CameraObject::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 temp;
    temp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    temp.y = sin(glm::radians(pitch));
    temp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(temp);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}

void CameraObject::ProcessInput(CAMERA_MOVEMENT direction, float deltaTime)
{
    float velocity = speed * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

void CameraObject::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void CameraObject::ProcessMouseScroll(float yoffset)
{
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

glm::mat4 CameraObject::GetViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}
CameraObject::~CameraObject() {}