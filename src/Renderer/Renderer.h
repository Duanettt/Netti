#pragma once

#include <glad/glad.h>
#include "../Backend/GLFW.h"
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Renderer/Cube.hpp"
#include <vector>
#include "Mesh.h"

// Forward declarations - help to tell Mr.Compiler that this class does exist within our codebase.
class Cube;

namespace Renderer 
{
    void RunEvents();

    // Create Vertex Array Objects.
    unsigned int CreateVAO(const float* vertices, size_t verticesSize, const unsigned int* indices, size_t indicesSize, int multiplier);
    unsigned int CreateVAO(const float* vertices, size_t verticesSize, int multiplier);

    unsigned int LoadTexture(const char* path, GLenum format);
    
    // Overloaded Render Functions
    void Render(Shader ourShader, unsigned int& VAO, unsigned int& texture);
    void Render(Shader ourShader, Mesh& mesh, unsigned int& texture1, unsigned int texture2, int screenHeight, int screenWidth, Camera& camera);
    void Render(Shader ourShader, float& deltaTime,std::vector<Mesh> meshes, unsigned int& texture1, unsigned int texture2, int screenHeight, int screenWidth, Camera& camera);

}
