#pragma once

#include "light.h"

class PointLight : public Light
{
private:
    glm::vec3 position;
    float constant, linear, quadratic;

public:
    PointLight(glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic) : Light(_ambient, _diffuse, _specular)
    {
        position = _position;
        constant = _constant;
        linear = _linear;
        quadratic = _quadratic;
    }

    glm::vec3 GetPositionVec3() { return position; }
    float GetConstant() { return constant; }
    float GetLinear() { return linear; }
    float GetQuadratic() { return quadratic; }

    void SetPosition(glm::vec3 _position){
        position = _position;
    }

    void SetUniform(Shader *shader){
        shader->SetUniformVec3("pointLights[0].position", position);
        shader->SetUniformVec3("pointLights[0].ambient", GetAmbientVec3());
        shader->SetUniformVec3("pointLights[0].diffuse", GetDiffuseVec3());
        shader->SetUniformVec3("pointLights[0].specular", GetSpecularVec3());
        shader->SetUniformFloat("pointLights[0].constant", constant);
        shader->SetUniformFloat("pointLights[0].linear", linear);
        shader->SetUniformFloat("pointLights[0].quadratic", quadratic);
    }

    ~PointLight(){};
};