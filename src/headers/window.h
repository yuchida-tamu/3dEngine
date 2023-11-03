#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class Window
{
private:
    GLFWwindow *mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;

    float deltaTime, lastFrame = 0.0f;

public:
    Window();

    int Initialize();
    GLFWwindow *GetWindow() { return mainWindow; }
    GLint GetBufferWidth() { return bufferWidth; }
    GLint GetBufferHeight() { return bufferHeight; }

    bool GetShouldClose() { return glfwWindowShouldClose(mainWindow); }
    void SwapBuffers() { glfwSwapBuffers(mainWindow); }

    void ProcessInput(CameraObject *camera);

    ~Window();
};