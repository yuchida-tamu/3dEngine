#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class Window
{
private:
    GLFWwindow *mainWindow;

    CameraObject *mainCamera;

    GLint width, height;
    GLint bufferWidth, bufferHeight;

    float deltaTime, lastFrame;

public:
    Window();

    int Initialize();

    GLint getBufferWidth() { return bufferWidth; }
    GLint getBufferHeight() { return bufferHeight; }

    CameraObject *getCamera() { return mainCamera; };

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void SwapBuffers() { glfwSwapBuffers(mainWindow); }
    void ProcessInput()
    {
        glm::vec3 cameraPos = mainCamera->getPosition();
        glm::vec3 cameraFront = mainCamera->getFront();
        glm::vec3 cameraUp = mainCamera->getUp();
        float cameraSpeed = mainCamera->getSpeed();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mainWindow, true);
        if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos + cameraSpeed * deltaTime * cameraFront);
        if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos - cameraSpeed * deltaTime * cameraFront);
        if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime);
        if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime);
    }

    ~Window();
};