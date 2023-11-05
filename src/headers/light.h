#pragma once

#include <glm/glm.hpp>
#include "shader.h"

class Light
{
private:
    glm::vec3 ambient, diffuse, specular;

public:
    Light(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular)
    {
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }

    glm::vec3 GetAmbientVec3() { return ambient; };
    glm::vec3 GetDiffuseVec3() { return diffuse; };
    glm::vec3 GetSpecularVec3() { return specular; };

    virtual void SetUniform(Shader *shader) = 0;

    ~Light()
    {
        ambient = glm::vec3(0);
        diffuse = glm::vec3(0);
        specular = glm::vec3(0);
    }
};