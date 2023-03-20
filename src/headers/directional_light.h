#pragma once

#include "light.h"

class DirectionalLight : public Light
{
private:
    glm::vec3 direction;

public:
    DirectionalLight(glm::vec3 _direction, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) : Light(_ambient, _diffuse, _specular)
    {
        direction = _direction;
    };
    glm::vec3 GetDirectionVec3() { return direction; };
};