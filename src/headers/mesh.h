#pragma once
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
    unsigned int VAO, VBO, EBO;
    unsigned int diffuseMap, specularMap;
    GLsizei indexCount;

    void prepareVertexData(GLfloat *vertices,
                           unsigned int *indices,
                           unsigned int verticesCount,
                           unsigned int indicesCount);
    unsigned int loadTexture(const char *texturePath);

public:
    Mesh();
    void CreateMesh(
        GLfloat *vertices,
        unsigned int *indices,
        unsigned int verticesCount,
        unsigned int indicesCount);
    void CreateMesh(
        GLfloat *vertices,
        unsigned int *indices,
        unsigned int verticesCount,
        unsigned int indicesCount,
        const char *diffuseMapPath);
    void CreateMesh(
        GLfloat *vertices,
        unsigned int *indices,
        unsigned int verticesCount,
        unsigned int indicesCount,
        const char *diffuseMapPath,
        const char *specularMapPath);

    unsigned int LoadDiffuseMap(const char *texturePath);
    unsigned int LoadSpecularMap(const char *texturePath);
    unsigned int GetDiffuseMap() { return diffuseMap; };
    unsigned int GetSpecularMap() { return specularMap; };
    void RenderMesh();
    void ClearMesh();
    ~Mesh();
};
