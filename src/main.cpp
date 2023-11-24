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
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

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
glm::vec3 lightPos(-2.0f, 3.0f, 0.5f);

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
    // glfwSetCursorPosCallback(mainWindow.GetWindow(), mouse_callback);


    create_objects();

    // build and compile our shader program
    create_shaders();

    glEnable(GL_DEPTH_TEST);

    // uncomment this call to draw in wire frame polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    SpotLight spotLight = SpotLight(
        mainCamera->GetPosition(),
        mainCamera->GetFront(),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0, 1.0f, 1.0f),
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(15.5f))
    );

    DirectionalLight dirLight = DirectionalLight(
        glm::vec3(-0.2f, -1.0f, -0.3f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(1.0, 1.0f, 1.0f));

    PointLight pointLight = PointLight(
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f,
        0.09f,
        0.032f
    );

    // render loop
    while (!mainWindow.GetShouldClose())
    {
        // input: camera movement
        mainWindow.ProcessInput(mainCamera);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // setup lighting
        spotLight.SetDirectionVec3(mainCamera->GetFront());
        spotLight.SetPositionVec3(mainCamera->GetPosition());
        spotLight.SetUniform(&shaderList[0]);
        pointLight.SetUniform(&shaderList[0]);
        dirLight.SetUniform(&shaderList[0]);

        // render Box
        render_meshes(&shaderList[0]);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        mainWindow.SwapBuffers();

        glfwPollEvents();
    }

    glUseProgram(0);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
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
    obj1->CreateMesh(basic_cube_vertices, indices, 288, 6, "src/resources/box_diffuse.png", "src/resources/box_specular.png");
    meshList.push_back(obj1);
}

glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, -2.0f);

void render_meshes(Shader *shader)
{

    shader->UseShader();

    shader->SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetUniformVec3("viewPos", mainCamera->GetPosition());

    // Material
    shader->SetUniformInt("material.diffuse", 0);
    shader->SetUniformInt("material.specular", 1);
    shader->SetUniformFloat("material.shininess", 64.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f) = glm::translate(model, cubePosition);
    float angle = 0.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = mainCamera->GetViewMatrix();

    shader->SetUniformMat4("view", view);
    shader->SetUniformMat4("model", model);
    shader->SetUniformMat4("projection", projection);
    meshList[0]->RenderMesh();
}
