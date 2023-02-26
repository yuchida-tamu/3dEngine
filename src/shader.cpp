#include "shader.h"

Shader::Shader(){
    shaderID = 0;
}

void Shader::CreateShaderFromFile(std::string vertFilePath, std::string fragFilePath){
   
    std::string vertString = ReadFile(vertFilePath);
    std::string fragString = ReadFile(fragFilePath);

    const GLchar* vertCode = vertString.c_str();
    const GLchar* fragCode = fragString.c_str();

    CompileShader(vertCode, fragCode);
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
   shaderList.push_back(shader);
}

std::string Shader::ReadFile(std::string filePath){
    std::string line, allLines, source;
    std::fstream vertFile(filePath);
   
    if (vertFile.is_open())
    {
        while (std::getline(vertFile, line))
        {
            source = source + line + "\n";
        }
        vertFile.close();
    }
    else
    {
        std::cout << "Unable to open file.";
        std::string result("");
        return result;
    }

    return source;
}

void Shader::UseShader(){

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderID, "ourColor");

    glUseProgram(shaderID);

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // delete shaders because they are not needed after being used by the shader program
    DeleteShaderObj();
}

void Shader::DeleteShaderObj(){
    for(GLuint shader : shaderList){
        glDeleteShader(shader);
    }
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