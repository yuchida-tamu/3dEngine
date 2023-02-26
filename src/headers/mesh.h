#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
        unsigned int indicesCount,
        const char* texturePath
    );
    void RenderMesh();
    void ClearMesh();
    ~Mesh();
};
