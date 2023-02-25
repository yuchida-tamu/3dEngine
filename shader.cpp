#include "shader.h"

Shader::Shader(){
    shaderID = 0;
}

void Shader::CreateShaderFromFile(const char vertFilePath[],const char fragFilePath[]){
    // read shader from the files and converted into char*

    // Compile(vertCode, fragCode)
}

void Shader::CreateShaderFromString(const char* vertString, const char* fragString){
    
    // Compile(vertCode, fragCode)
    CompileShader(vertString, fragString);
}



void Shader::CompileShader(const char* vertCode,const char* fragCode){
    shaderID = glCreateProgram();
   
    AddShader(shaderID, vertCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragCode, GL_FRAGMENT_SHADER);

    glLinkProgram(shaderID);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::AddShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    const GLchar* shaderCodeBuffer[1];
    shaderCodeBuffer[0] = shaderCode;

     GLint codeLength[1];
     codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, shaderCodeBuffer, codeLength);
    glCompileShader(shader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
   
   glAttachShader(shaderProgram, shader);
}

void Shader::UseShader(){
    glUseProgram(shaderID);
}

void Shader::ClearShader(){
    if(shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}


Shader::~Shader(){
    ClearShader();
}