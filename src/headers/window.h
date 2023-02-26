#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    private: 
        GLFWwindow* mainWindow;

        GLint width, height;
        GLint bufferWidth, bufferHeight;

    public:
        Window();

        int Initialize();

        GLint getBufferWidth() { return bufferWidth; }
        GLint getBufferHeight() { return bufferHeight; }

        bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

        void SwapBuffers() { glfwSwapBuffers(mainWindow); }
        void ProcessInput(){
            if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mainWindow, true);
        }

        ~Window();
};