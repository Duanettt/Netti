#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Mesh.h"

#include "utils/Data.h"
#include <iostream>

class Quad : public Mesh
{
public:
	Quad() : Mesh()
	{
        std::vector<Vertex> vertices = {
            // positions         // normals (placeholders)  // texture coords
            { glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) }, // top right
            { glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) }, // bottom right
            { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) }, // bottom left
            { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) }  // top left
        };

        std::vector<unsigned int> indices = {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
        };

        uploadVertexData(vertices, indices);
	}
    // Issue cannot render different objects.
    void Draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
private:
};

