#include "camera.h"

CameraObject::CameraObject()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 0.05f;
}

CameraObject::~CameraObject() {}