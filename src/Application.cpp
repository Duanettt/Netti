#include "Application.h"
#include "./Renderer/Renderer.h"
#include "./Renderer/Cube.h"
#include "Renderer/utils/Data.h"
#include "Renderer/Mesh.h"
#include "Renderer/Quad.h"


// settings
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;
int  success;
char infoLog[512];

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera;

bool firstMouse = true;
int lastX = 800 / 2;
int lastY = 600 / 2;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 position = glm::vec3(2.0f, 5.0f, -15.0f);
glm::vec3 cube2Position = glm::vec3(-3.8f, -2.0f, -12.3f);
std::vector<Mesh> meshes; 

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
    GLFW::InitializeWindow(screenWidth, screenHeight, "LearnOpenGL");
    glfwSetCursorPosCallback(window, mouse_callback);

    glm::vec3 cubePositions[] = {
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

    Quad quad;

    quad.applyRotate(glm::vec3(1.0f, 0.0f, 0.0f), -55.0f);

    meshes.push_back(quad);

    int i = 0; 
    while (i < 10)
    {
        Cube cube;
        cube.applyTranslate(cubePositions[i]);
        cube.applyGravity();
        meshes.push_back(cube);
        i++;
    } 

    unsigned int texture1 = Renderer::LoadTexture("./res/textures/LearnOpenGL/container.jpg", GL_RGB);
    unsigned int texture2 = Renderer::LoadTexture("./res/textures/LearnOpenGL/awesomeface.png", GL_RGBA);


    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    //cube.applyTranslate(position);

    //cube2.applyTranslate(cube2Position);
    glm::vec3 pCubePosition = glm::vec3(0.0f);
    glm::vec3 pCubeVelocity = glm::vec3(0.1f);
    glm::vec3 pCubeAcceleration = glm::vec3(0.5f);
    float pCubeMass = 1.0f;

    for(Mesh& mesh : meshes)
    {
        mesh.physics.setPosition(pCubePosition);
        mesh.physics.setAcceleration(pCubeAcceleration);
        mesh.physics.setVelocity(pCubeVelocity);
        mesh.physics.setMass(pCubeMass);
    }

    while (GLFW::WindowIsOpen())
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        GLFW::ProcessInput(camera, deltaTime);
        Renderer::RunEvents();


        for (Mesh& mesh : meshes)
        {
            mesh.applyGravity();
            mesh.updatePhysics(deltaTime);
        }

        //Renderer::Render(ourShader, cube, texture1, texture2, 800, 600, camera);
        //Renderer::Render(ourShader, cube2, texture1, texture2, 800, 600); 

        Renderer::Render(ourShader, deltaTime, meshes, texture1, texture2, 800, 600, camera);

    }
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;


    camera.ProcessMouseMovement(xoffset, yoffset);
}
