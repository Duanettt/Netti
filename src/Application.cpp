#include "Application.h"
#include "./Renderer/Renderer.h"
#include "./Renderer/Cube.h"


// settings
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;
int  success;
char infoLog[512];


int main()
{
    GLFW::InitializeWindow(screenWidth, screenHeight, "LearnOpenGL");

    Shader ourShader("./res/shaders/vertexShader.vert", "./res/shaders/fragmentShader.frag");

    glEnable(GL_DEPTH_TEST);

    Cube cube;

    unsigned int texture1 = Renderer::LoadTexture("./res/textures/LearnOpenGL/container.jpg", GL_RGB);
    unsigned int texture2 = Renderer::LoadTexture("./res/textures/LearnOpenGL/awesomeface.png", GL_RGBA);


    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    while (GLFW::WindowIsOpen())
    {
        GLFW::ProcessInput();
        Renderer::RunEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        cube.Transformations(ourShader);
        cube.Draw();

    }
}