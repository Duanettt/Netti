#include "GLFW.h"

GLFWwindow* window;
int width;
int height;
const char* title;

void GLFW::ProcessInput(Camera& camera, float& deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    const float cameraSpeed = 0.05f; // adjust accordinglyw
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }


    // Camera Speed Statements
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DECREASE, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(INCREASE, deltaTime);
    }
}

void GLFW::ProcessInput(float mixValue)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}




void GLFW::Terminate()
{
    if (window != nullptr) 
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

bool GLFW::WindowIsOpen()
{
    return !glfwWindowShouldClose(window);
}

void GLFW::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool GLFW::InitializeWindow(const unsigned int& w,const unsigned int& h, const char* t)
{

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(w, h, t, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Terminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        Terminate();
        return false;
    }

    return true;
}
