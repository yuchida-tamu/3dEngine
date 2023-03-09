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
#include "mesh_data.h"

Window mainWindow;
CameraObject *mainCamera;

std::vector<Shader> shaderList;
std::vector<Mesh *> meshList;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
double lastX = 0.0;
double lastY = 0.0;
float xoffset = 0.0f;
float yoffset = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 3.0f, 2.0f);

void create_shaders();
void create_objects();
void render_meshes(Shader *shader);
void processInput(GLFWwindow *window, CameraObject *camera);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

int main()
{
    mainWindow = Window();
    mainWindow.Initialize();
    mainCamera = new CameraObject();
    glfwSetCursorPosCallback(mainWindow.GetWindow(), mouse_callback);

    create_objects();

    // Light Object
    unsigned int lightVAO, lightVBO;
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(light_cube_vertices), light_cube_vertices, GL_STATIC_DRAW);

    glBindVertexArray(lightVAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // build and compile our shader program
    create_shaders();

    Shader lightingShader = Shader("src/shaders/lighting.vs", "src/shaders/lighting.fs");

    glEnable(GL_DEPTH_TEST);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!mainWindow.GetShouldClose())
    {

        // input
        processInput(mainWindow.GetWindow(), mainCamera);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render Box
        render_meshes(&shaderList[0]);

        // render lighting object
        lightingShader.UseShader();
        lightingShader.SetUniformVec3("objectColor", glm::vec3(1.0f, 0.0f, 1.0f));

        glm::mat4 lightView = mainCamera->GetViewMatrix();
        int lightViewLocation = lightingShader.GetUniformView();
        glUniformMatrix4fv(lightViewLocation, 1, GL_FALSE, glm::value_ptr(lightView));
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        int projectLocation = lightingShader.GetUniformProjection();
        int lightModelLocation = lightingShader.GetUniformModel();
        glUniformMatrix4fv(projectLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(lightModelLocation, 1, GL_FALSE, glm::value_ptr(lightModel));
        // render the cube
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        mainWindow.SwapBuffers();

        glfwPollEvents();
    }

    glUseProgram(0);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, CameraObject *camera)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessInput(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessInput(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessInput(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessInput(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    mainCamera->ProcessMouseMovement(xoffset, yoffset);
}

void create_shaders()
{
    Shader *shader1 = new Shader("src/shaders/shader.vert", "src/shaders/shader.frag");
    shaderList.push_back(*shader1);
}

void create_objects()
{
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMeshWithTexture(basic_cube_vertices, indices, 288, 6, "src/resources/wall.jpg");
    meshList.push_back(obj1);
}

void render_meshes(Shader *shader)
{

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f) = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    for (Mesh *mesh : meshList)
    {
        shader->UseShader();
        shader->SetUniformTextureIndex("texture01", 0);
        glm::mat4 view = mainCamera->GetViewMatrix();

        shader->SetUniformMat4("view", view);
        shader->SetUniformMat4("model", model);
        shader->SetUniformMat4("projection", projection);

        shader->SetUniformVec3("lightColor", glm::vec3(0.0f, 1.0f, 1.0f));
        shader->SetUniformVec3("lightPos", lightPos);

        shader->SetUniformVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
        shader->SetUniformVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
        shader->SetUniformVec3("material.specular", glm::vec3(1.0f, 0.5f, 0.31f));
        shader->SetUnifromFloat("material.shininess", 100.0f);

        shader->SetUniformVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        shader->SetUniformVec3("light.diffuse", glm::vec3(0.2f, 0.0f, 0.2f)); // darken diffuse light a bit
        shader->SetUniformVec3("light.specular", glm::vec3(0.2f, 0.0f, 0.2f));

        shader->SetUniformVec3("viewPos", mainCamera->GetPosition());

        mesh->RenderMesh();
    }
}