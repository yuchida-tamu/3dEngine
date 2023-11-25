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
    glfwSetCursorPosCallback(mainWindow.GetWindow(), mouse_callback);

    shader1 = new Shader("src/shaders/shader.vert", "src/shaders/shader.frag");    
    Shader *gridShader = new Shader("src/shaders/grid.vs", "src/shaders/grid.fs");   

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Prepare a Box object
    Mesh *boxMesh = new Mesh();
    boxMesh->CreateMesh(basic_cube_vertices, indices, 288, 6, "src/resources/box_diffuse.png", "src/resources/box_specular.png");
    GameObject *boxObject = new GameObject(mainCamera, boxMesh);

    // Grid Mesh 
        uint VAO = 0;
        uint VBO = 0;
        float vertices[] = {
            1.0f,   1.0f,   0.0f,
            -1.0f,  1.0f,   0.0f,
            -1.0f,  -1.0f,  0.0f,
            -1.0f,  -1.0f,  0.0f,
            1.0f,   -1.0f,  0.0f,
            1.0f,   1.0f,   0.0f
        };

        glGenVertexArrays(1, &VAO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);



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
        gridShader->UseShader();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::mat4(1.0f) = glm::translate(model, glm::vec3{
                0.0f, 0.0f, 0.0f
            });
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
            glm::mat4 view = mainCamera->GetViewMatrix();
            gridShader->SetUniformMat4("view", view);
            gridShader->SetUniformMat4("model", model);
            gridShader->SetUniformMat4("projection", projection);
            // Draw
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
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
