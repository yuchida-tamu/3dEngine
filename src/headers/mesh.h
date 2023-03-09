#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <iostream>

class Mesh
{
private:
    unsigned int VAO, VBO, EBO, texture;
    GLsizei indexCount;

public:
    Mesh();
    void CreateMesh(
        GLfloat *vertices,
        unsigned int *indices,
        unsigned int verticesCount,
        unsigned int indicesCount);
    void AddTexture(const char *texturePath);
    void RenderMesh();
    void ClearMesh();
    ~Mesh();
};
