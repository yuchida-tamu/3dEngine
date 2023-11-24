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
#include "game_object.h"

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

Shader *shader1;

// lighting
glm::vec3 lightPos(-2.0f, 3.0f, 0.5f);
std::vector<Light *> lightList;

void processInput(GLFWwindow *window, CameraObject *camera);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void setup_lights();


int main()
{
    mainWindow = Window();
    mainWindow.Initialize();
    mainCamera = new CameraObject();
    // glfwSetCursorPosCallback(mainWindow.GetWindow(), mouse_callback);

    shader1 = new Shader("src/shaders/shader.vert", "src/shaders/shader.frag");    

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Prepare a Box object
    Mesh *boxMesh = new Mesh();
    boxMesh->CreateMesh(basic_cube_vertices, indices, 288, 6, "src/resources/box_diffuse.png", "src/resources/box_specular.png");
    GameObject *boxObject = new GameObject(mainCamera, boxMesh);

    // Prepare lights
    setup_lights();
    SpotLight * spotLight = new SpotLight(
        mainCamera->GetPosition(),
        mainCamera->GetFront(),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0, 1.0f, 1.0f),
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(15.5f))
    );

    glEnable(GL_DEPTH_TEST);

    // uncomment this call to draw in wire frame polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // render loop
    while (!mainWindow.GetShouldClose())
    {
        // input: camera movement
        mainWindow.ProcessInput(mainCamera);

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render Box
        shader1->UseShader();
        shader1->SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader1->SetUniformVec3("viewPos", mainCamera->GetPosition());;
        for(Light* light : lightList)
        {
            light->SetUniform(shader1);
        }
        spotLight->SetDirectionVec3(mainCamera->GetFront());
        spotLight->SetPositionVec3(mainCamera->GetPosition());
        spotLight->SetUniform(shader1);
   
        boxObject->Render(shader1);
        glUseProgram(0);

        
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

void setup_lights()
{
   

    DirectionalLight *dirLight = new DirectionalLight(
        glm::vec3(-0.2f, -1.0f, -0.3f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(1.0, 1.0f, 1.0f));

    PointLight *pointLight = new PointLight(
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f,
        0.09f,
        0.032f
    );
 
    lightList.push_back(dirLight);
    lightList.push_back(pointLight);

}
