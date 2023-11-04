#pragma once
#include "light.h"

class SpotLight : public Light
{
private:
    glm::vec3 position, direction;
    float innerCutOff, outerCutOff;

public:
    SpotLight(
        glm::vec3 _position, 
        glm::vec3 _direction, 
        glm::vec3 _ambient, 
        glm::vec3 _diffuse, 
        glm::vec3 _specular,
        float _innerCutOff,
        float _outerCutOff
        ) : Light(_ambient, _diffuse, _specular)
    {
        position = _position;
        direction = _direction;
        innerCutOff = _innerCutOff;
        outerCutOff = _outerCutOff;
    }

    glm::vec3 GetPositionVec3() { return position; }
    glm::vec3 GetDirectionVec3() { return direction; }
    float GetInnerCutOff() { return innerCutOff; }
    float GetOuterCutOff() { return outerCutOff; }

    ~SpotLight() {}
};