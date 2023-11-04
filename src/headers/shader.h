#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

class Shader
{
private:
    GLuint shaderID, uniformProjection, uniformView, uniformModel;

    void compileShader(const char *vertCode, const char *fragCode);
    unsigned int addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
    std::string readFile(std::string filePath);
public:
    Shader();
    Shader(std::string vertFilePath, std::string fragFilePath);

    void CreateShaderFromFile(std::string vertFilePath, std::string fragFilePath);
    void CreateShaderFromString(const char *vertString, const char *fragString);
    void SetUniformInt(const char* name, int value );
    void SetUniformFloat(const char* name, float value);
    void SetUniformVec3(const char* name, glm::vec3 vec);
    void SetUniformMat4(const char* name, glm::mat4 vec);
    void SetUniformTextureIndex(const char* name, uint );
    // Lighting
    void SetUniformDirectionalLight(DirectionalLight light);
    void SetUniformPointLight(PointLight light, glm::vec3 position);
    void SetUniformSpotLight(SpotLight light);

    GLuint GetUniformProjection() { return uniformProjection; };
    GLuint GetUniformView() { return uniformView; };
    GLuint GetUniformModel() { return uniformModel; };

    void UseShader();
    void ClearShader();

    ~Shader();

};