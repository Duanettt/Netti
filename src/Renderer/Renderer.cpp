#include "Renderer.h"


// settings
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;
int  success;
char infoLog[512];

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


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
    // 


    // create shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    };



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
