#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "mesh.h"
#include "window.h"

Window mainWindow;
std::vector<Shader> shaderList;
std::vector<Mesh *> meshList;

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateShaderFromFile("src/shaders/shader.vert", "src/shaders/shader.frag");
    shaderList.push_back(*shader1);
}

void CreateObjects()
{
    float vertices[] = {
        // first triangle
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 6);
    meshList.push_back(obj1);
}

void RenderMeshes()
{
    for (Mesh *mesh : meshList)
    {
        mesh->RenderMesh();
    }
}

int main()
{
    mainWindow = Window();
    mainWindow.Initialize();

    CreateObjects();
    // build and compile our shader program
    CreateShaders();

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!mainWindow.getShouldClose())
    {
        
        // input
        mainWindow.ProcessInput();

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderList[0].UseShader();
        meshList[0]->RenderMesh();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        mainWindow.SwapBuffers();

        glfwPollEvents();
    }

    glUseProgram(0);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
