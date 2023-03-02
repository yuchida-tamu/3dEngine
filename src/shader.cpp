#include "shader.h"

Shader::Shader(){
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0; 
}

void Shader::CreateShaderFromFile(std::string vertFilePath, std::string fragFilePath){
   
    std::string vertString = readFile(vertFilePath);
    std::string fragString = readFile(fragFilePath);

    const GLchar* vertCode = vertString.c_str();
    const GLchar* fragCode = fragString.c_str();

    compileShader(vertCode, fragCode);
}

void Shader::CreateShaderFromString(const char* vertString, const char* fragString){
    
    // Compile(vertCode, fragCode)
    compileShader(vertString, fragString);
}
void Shader::UseShader(){
    glUseProgram(shaderID);
    // create func to set uniform location
    glUniform1i(glGetUniformLocation(shaderID, "texture01"), 0);
    glUniform1i(glGetUniformLocation(shaderID, "texture02"), 1);

    // delete shaders because they are not needed after being used by the shader program
    deleteShaderObj();
}

void Shader::ClearShader(){
    if(shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}

void Shader::compileShader(const char* vertCode,const char* fragCode){
    shaderID = glCreateProgram();
   
    addShader(shaderID, vertCode, GL_VERTEX_SHADER);
    addShader(shaderID, fragCode, GL_FRAGMENT_SHADER);

    glLinkProgram(shaderID);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformModel = glGetUniformLocation(shaderID, "model");
}

void Shader::addShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType){
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

std::string Shader::readFile(std::string filePath){
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

void Shader::deleteShaderObj(){
    for(GLuint shader : shaderList){
        glDeleteShader(shader);
    }
}

Shader::~Shader(){
    ClearShader();
}