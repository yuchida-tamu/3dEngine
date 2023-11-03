#include "window.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Window::Window()
{
    width = SCR_WIDTH;
    height = SCR_HEIGHT;
}

int Window::Initialize()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    mainWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (mainWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mainWindow);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    

    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

void Window::ProcessInput(CameraObject *camera){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mainWindow, true);
    if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessInput(FORWARD, deltaTime);
    if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessInput(BACKWARD, deltaTime);
    if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessInput(LEFT, deltaTime);
    if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessInput(RIGHT, deltaTime);
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}