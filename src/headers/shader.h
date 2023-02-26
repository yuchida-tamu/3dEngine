#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Shader {
    public:
        Shader();

        void CreateShaderFromFile(std::string vertFilePath, std::string fragFilePath);
        void CreateShaderFromString(const char* vertString, const char* fragString);

        void UseShader();
        void ClearShader();

        ~Shader();

    private:
        GLuint shaderID;
        std::vector<GLuint> shaderList;

        void CompileShader(const char* vertCode,const char* fragCode);
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        void DeleteShaderObj();
        std::string ReadFile(std::string filePath);

};