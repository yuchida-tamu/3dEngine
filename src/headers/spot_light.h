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

    void SetPositionVec3( glm::vec3 _position ){ position = _position; }
    void SetDirectionVec3( glm::vec3 _direction ){ direction = _direction; }

    void SetUniform(Shader *shader){
        shader->SetUniformVec3("spotLight.position", position);
        shader->SetUniformVec3("spotLight.direction", direction);
        shader->SetUniformVec3("spotLight.ambient", GetAmbientVec3());
        shader->SetUniformVec3("spotLight.diffuse", GetDiffuseVec3()); // darken diffuse light a bit
        shader->SetUniformVec3("spotLight.specular", GetSpecularVec3());
        shader->SetUniformFloat("spotLight.innerCutOff", innerCutOff);
        shader->SetUniformFloat("spotLight.outerCutOff", outerCutOff);
    }

    float GetInnerCutOff() { return innerCutOff; }
    float GetOuterCutOff() { return outerCutOff; }

    ~SpotLight() {};
};