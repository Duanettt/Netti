#include "Renderer.h"


// settings
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;


int main()
{
    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Firstly we must communicate with our GPU/Shaders VIA allocation memory in our GPU for our vertex data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // We then bind our buffer so we place our bufferdata into it.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLFW::InitializeWindow(screenWidth, screenHeight, "LearnOpenGL");

    while (GLFW::WindowIsOpen())
    {
        GLFW::ProcessInput();
        Renderer::RunEvents();
        Renderer::Render();


    }
}


void Renderer::RunEvents()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}


void Renderer::Render()
{
    glClearColor(0.17f, 0.17f, 0.17f, 0.17f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Render your objects here

}
