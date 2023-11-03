#include "shader.h"

Shader::Shader()
{
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
}
Shader::Shader(std::string vertFilePath, std::string fragFilePath)
{
    CreateShaderFromFile(vertFilePath, fragFilePath);
}

void Shader::CreateShaderFromFile(std::string vertFilePath, std::string fragFilePath)
{

    std::string vertString = readFile(vertFilePath);
    std::string fragString = readFile(fragFilePath);

    const GLchar *vertCode = vertString.c_str();
    const GLchar *fragCode = fragString.c_str();

    compileShader(vertCode, fragCode);
}

void Shader::CreateShaderFromString(const char *vertString, const char *fragString)
{
    compileShader(vertString, fragString);
}
void Shader::UseShader()
{
    glUseProgram(shaderID);
}

void Shader::SetUniformInt(const char* name, int value){
    GLuint uniformLoc = glGetUniformLocation(shaderID, name);
    glUniform1i(uniformLoc, value);
}

void Shader::SetUniformFloat(const char* name, float value){
    GLuint uniformLoc = glGetUniformLocation(shaderID, name);
    glUniform1f(uniformLoc, value);
}

void Shader::SetUniformVec3(const char *name, glm::vec3 vec)
{
    GLuint uniformLoc = glGetUniformLocation(shaderID, name);
    glUniform3fv(uniformLoc, 1, glm::value_ptr(vec));
}

void Shader::SetUniformMat4(const char *name, glm::mat4 mat)
{
    GLuint uniformLoc = glGetUniformLocation(shaderID, name);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetUniformTextureIndex(const char *name, GLuint index)
{
    GLuint uniformLoc = glGetUniformLocation(shaderID, name);
    glUniform1i(uniformLoc, index);
}

void Shader::SetUniformDirectionalLight(DirectionalLight light){
    SetUniformVec3("directionalLight.direction", light.GetDirectionVec3());
    SetUniformVec3("directionalLight.ambient", light.GetAmbientVec3());
    SetUniformVec3("directionalLight.diffuse", light.GetDiffuseVec3());
    SetUniformVec3("directionalLight.specular", light.GetSpecularVec3());
}

void Shader::SetUniformPointLight(PointLight light, glm::vec3 position){
   SetUniformVec3("pointLights[0].position", position);
   SetUniformVec3("pointLights[0].ambient", light.GetAmbientVec3());
   SetUniformVec3("pointLights[0].diffuse", light.GetDiffuseVec3());
   SetUniformVec3("pointLights[0].specular", light.GetSpecularVec3());
   SetUniformFloat("pointLights[0].constant", light.GetConstant());
   SetUniformFloat("pointLights[0].linear", light.GetLinear());
   SetUniformFloat("pointLights[0].quadratic", light.GetQuadratic());
}

void Shader::ClearShader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}

void Shader::compileShader(const char *vertCode, const char *fragCode)
{
    shaderID = glCreateProgram();

    unsigned int vertex = addShader(shaderID, vertCode, GL_VERTEX_SHADER);
    unsigned int frag = addShader(shaderID, fragCode, GL_FRAGMENT_SHADER);

    glLinkProgram(shaderID);

    glDeleteShader(vertex);
    glDeleteShader(frag);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformModel = glGetUniformLocation(shaderID, "model");
}

unsigned int Shader::addShader(GLuint shaderProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    const GLchar *shaderCodeBuffer[1];
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    glAttachShader(shaderProgram, shader);

    return shader;
}

std::string Shader::readFile(std::string filePath)
{
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

Shader::~Shader()
{
    ClearShader();
}