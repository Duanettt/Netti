#include "Application.h"
#include "./Renderer/Renderer.h"
#include "./Renderer/Cube.h"


// settings
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;
int  success;
char infoLog[512];

glm::vec3 position = glm::vec3(2.0f, 5.0f, -15.0f);
glm::vec3 cube2Position = glm::vec3(-3.8f, -2.0f, -12.3f);
std::vector<Cube> cubes; 


int main()
{
    GLFW::InitializeWindow(screenWidth, screenHeight, "LearnOpenGL");

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    Shader ourShader("./res/shaders/vertexShader.vert", "./res/shaders/fragmentShader.frag");

    glEnable(GL_DEPTH_TEST);

    Cube cube;

    Cube cube2;

    int i = 0; 
    while (i < 10)
    {
        Cube cube;
        cube.applyTranslate(cubePositions[i]);
        cubes.push_back(cube);
        i++;
    }

    unsigned int texture1 = Renderer::LoadTexture("./res/textures/LearnOpenGL/container.jpg", GL_RGB);
    unsigned int texture2 = Renderer::LoadTexture("./res/textures/LearnOpenGL/awesomeface.png", GL_RGBA);


    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    cube.applyTranslate(position);

    cube2.applyTranslate(cube2Position);

    while (GLFW::WindowIsOpen())
    {
        GLFW::ProcessInput();
        Renderer::RunEvents();


       /* Renderer::Render(ourShader, cube, texture1, texture2, 800, 600);
        Renderer::Render(ourShader, cube2, texture1, texture2, 800, 600); */

        Renderer::Render(ourShader, cubes, texture1, texture2, 800, 600);

    }
}