#pragma once

#include <glm/glm.hpp>

class CameraObject
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float speed;

public:
    CameraObject();

    glm::vec3 getPosition() { return position; };
    glm::vec3 getFront() { return front; };
    glm::vec3 getUp() { return up; };
    float getSpeed() { return speed; };
    void updatePosition(glm::vec3 pos) { position = pos; };

    ~CameraObject();
};