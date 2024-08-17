#include "Application.h"

// settings
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 600;
int  success;
char infoLog[512];

bool isFPSmode = true;

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

int mesh_selected = -1;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    GLFW::InitializeWindow(screenWidth, screenHeight, "LearnOpenGL");
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls     // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    Shader ourShader("./res/shaders/vertexShader.vert", "./res/shaders/fragmentShader.frag");
    Shader lightCubeShader("./res/shaders/lightCubeShader.vert", "./res/shaders/lightCubeShader.frag");

    glEnable(GL_DEPTH_TEST);


    int i = 0;
    /*    while (i < 10)
        {
            Cube cube;
            cube.applyTranslate(cubePositions[i]);
            cube.applyGravity();
            meshes.push_back(cube);
            i++;
        } */

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

    for (Mesh& mesh : meshes)
        {
            mesh.physics.setPosition(pCubePosition);
            mesh.physics.setAcceleration(pCubeAcceleration);
            mesh.physics.setVelocity(pCubeVelocity);
            mesh.physics.setMass(pCubeMass);
        } 

    bool buttonIsPressed = false;

    while (GLFW::WindowIsOpen())
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Generates our cube upon clicks

        if (ImGui::Button("Generate cube"))
        {
            Cube cube;
            meshes.push_back(cube);
        }

        if (ImGui::Button("Generate quad"))
        {
            Quad quad;
            meshes.push_back(quad);
        }

        // Listbox basically lists the cubes in a mesh etcetera.

        if (ImGui::BeginListBox("ListBox"))
        {
            for (int i = 0; i < meshes.size(); i++)
            {
                // Checks if we've selected the mesh.
                if (ImGui::Selectable(meshes[i].name.c_str(), mesh_selected))
                {
                    mesh_selected = i;
                }
            }
            ImGui::EndListBox();
        }

        static glm::vec3 tempPosition;

        if (mesh_selected != -1)
        {
            Mesh& selectedMesh = meshes[mesh_selected];
            glm::vec3 position = selectedMesh.getPosition();

            // Doesn't work right now try to fix later.

            int lastSelected = -1;

            if (lastSelected != mesh_selected)
            {
                tempPosition = selectedMesh.getPosition();
                lastSelected = mesh_selected;
            }

            ImGui::Text("Selected Mesh: %s", selectedMesh.name.c_str());

            if (ImGui::SliderFloat3("Position", glm::value_ptr(position), 0.1f, 1.0))
            {
                selectedMesh.applyTranslate(position);
            }
        }

        GLFW::ProcessInput(camera, deltaTime);
        Renderer::RunEvents();

        if (ImGui::Button("Apply gravity"))
        {
            buttonIsPressed = !buttonIsPressed;
        }

        if (buttonIsPressed)
        {
            for (Mesh& mesh : meshes)
            {
                mesh.applyGravity();
                mesh.updatePhysics(deltaTime);
            }
        };

        //Renderer::Render(ourShader, cube, texture1, texture2, 800, 600, camera);
        //Renderer::Render(ourShader, cube2, texture1, texture2, 800, 600); 

        Renderer::Render(ourShader, deltaTime, meshes, texture1, texture2, 800, 600, camera);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        isFPSmode = !isFPSmode;
        if (isFPSmode)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}
