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

#include "renderer.h"
#include "grid.h"

#include "shaders_paths.h"

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

bool isGridMode = true;

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

    glfwSetCursorPosCallback(mainWindow.GetWindow(), mouse_callback);

    shader1 = new Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);    
    
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Prepare a Box object
    Mesh *boxMesh = new Mesh();
    boxMesh->CreateMesh(basic_cube_vertices, indices, 288, 6,   "/Users/yutauchida/Projects/openGl/3dEngine/src/resources/box_diffuse.png", "/Users/yutauchida/Projects/openGl/3dEngine/src/resources/box_specular.png");
    GameObject *boxObject = new GameObject(mainCamera, boxMesh);

    // Grid Mesh 
    Grid *grid = new Grid();
    grid->Initialize();



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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // uncomment this call to draw in wire frame polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!mainWindow.GetShouldClose())
    {
        // input: camera movement
        mainWindow.ProcessInput(mainCamera);

        // toggle grid view mode
        if (glfwGetKey( mainWindow.GetWindow(), GLFW_KEY_0) == GLFW_PRESS){
            isGridMode = false;
        }

        if (glfwGetKey( mainWindow.GetWindow(), GLFW_KEY_9) == GLFW_PRESS){
            isGridMode = true;
        }

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render Box
            // update the position and direction of a spot light before rendering,
            // and push that into the light list
            spotLight->SetDirectionVec3(mainCamera->GetFront());
            spotLight->SetPositionVec3(mainCamera->GetPosition());
            lightList.push_back(spotLight);
            Renderer::RenderScene(mainCamera, shader1, std::vector{boxObject}, lightList);
            // discard the spot light from the list for next update
            lightList.pop_back();

        // render Grid
        if(isGridMode)
        {
          grid->Render(mainCamera);
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
