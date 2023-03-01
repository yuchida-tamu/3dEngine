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

        if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mainWindow, true);
        if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos + cameraSpeed * cameraFront);
        if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos - cameraSpeed * cameraFront);
        if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
        if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
            mainCamera->updatePosition(cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
    }

    ~Window();
};