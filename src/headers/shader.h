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

class Shader
{
private:
    GLuint shaderID, uniformProjection, uniformView, uniformModel;
    std::vector<GLuint> shaderList;

    void compileShader(const char *vertCode, const char *fragCode);
    void addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
    void deleteShaderObj();
    std::string readFile(std::string filePath);
public:
    Shader();

    void CreateShaderFromFile(std::string vertFilePath, std::string fragFilePath);
    void CreateShaderFromString(const char *vertString, const char *fragString);

    GLuint GetUniformProjection() { return uniformProjection; };
    GLuint GetUniformView() { return uniformView; };
    GLuint GetUniformModel() { return uniformModel; };

    void UseShader();
    void ClearShader();

    ~Shader();

};