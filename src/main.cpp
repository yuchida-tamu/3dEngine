#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include "shader.h"
#include "mesh.h"
#include "window.h"
#include "camera.h"

Window mainWindow;
CameraObject *mainCamera;

std::vector<Shader> shaderList;
std::vector<Mesh *> meshList;

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f),
    glm::vec3(1.0f, 0.2f, 0.0f),
    glm::vec3(2.5f, 6.4f, -15.0f),
    glm::vec3(-1.5f, -1.2f, -2.5f),
    glm::vec3(-3.8f, -4.5f, -10.3f),
    glm::vec3(2.4f, -0.4f, -4.5f),
    glm::vec3(-1.7f, 3.0f, -7.0f),
    glm::vec3(1.0f, -2.4f, -1.5f),
    glm::vec3(1.2f, 2.0f, -2.5f),
    glm::vec3(1.5f, 1.2f, -1.5f),
    glm::vec3(-1.5f, 0.0f, -3.5f),
};

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateShaderFromFile("src/shaders/shader.vert", "src/shaders/shader.frag");
    shaderList.push_back(*shader1);
}

void CreateObjects()
{
    // float vertices[] = {
    //     // positions        //colors
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
    // };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 180, 6, "src/resources/wall.jpg");
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
    mainCamera = mainWindow.getCamera();


    CreateObjects();
    // build and compile our shader program
    CreateShaders();

    glEnable(GL_DEPTH_TEST);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    std::vector<glm::vec3> positions;

    for (unsigned int i = 0; i < 100; i++)
    {
        glm::vec3 pos = glm::vec3(glm::ballRand(5.0f).x, glm::ballRand(5.0f).y, glm::linearRand(0.0f, -40.0f));

        positions.push_back(pos);
    }

    // render loop
    while (!mainWindow.getShouldClose())
    {

        // input
        mainWindow.ProcessInput();

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();

        glm::vec3 cameraPos = mainCamera->getPosition();
        glm::vec3 cameraFront = mainCamera->getFront();
        glm::vec3 cameraUp = mainCamera->getUp();

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        int viewLocation = shaderList[0].GetUniformView();
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        for (unsigned int i = 0; i < 100; i++)
        {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f * i / 10), glm::vec3(1.0f * i / 10, 0.5f * i / 10, 0.2f * i / 10));
            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            int projectLocation = shaderList[0].GetUniformProjection();
            int modelLocation = shaderList[0].GetUniformModel();
            glUniformMatrix4fv(projectLocation, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

            meshList[0]->RenderMesh();
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        mainWindow.SwapBuffers();

        glfwPollEvents();
    }

    glUseProgram(0);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
