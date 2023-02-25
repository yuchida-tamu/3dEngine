#pragma once

#include <iostream>
#include <cstring>

#include <glad/glad.h>

class Shader {
    public:
        Shader();

        void CreateShaderFromFile(const char vertFilePath[],const char fragFilePath[]);
        void CreateShaderFromString(const char* vertString, const char* fragString);

        void UseShader();
        void ClearShader();

        ~Shader();

    private:
        GLuint shaderID;

        void CompileShader(const char* vertCode,const char* fragCode);
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

};