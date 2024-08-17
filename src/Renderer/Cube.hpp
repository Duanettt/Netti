#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "Mesh.h"

#include "utils/Data.h"
#include <iostream>
#include <vector>


class Cube : public Mesh
{
public:
    // Static variables are shared amongst all instances of a class.
    static int cubeCounter;

    glm::mat4 _model = glm::mat4(1.0f);

    Cube() : Mesh("Cube" + std::to_string(++cubeCounter))
    {
        std::vector<Vertex> vertices = {
            // positions          // normals         // texture coords
            { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },

            { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },

            { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },

            { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },

            { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f) },
            { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },

            { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f) },
            { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f) },
            { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
            { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f) },
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0,   // Front face
            4, 5, 6, 6, 7, 4,   // Back face
            8, 9, 10, 10, 11, 8, // Left face
            12, 13, 14, 14, 15, 12, // Right face
            16, 17, 18, 18, 19, 16, // Top face
            20, 21, 22, 22, 23, 20  // Bottom face
        };


        uploadVertexData(vertices, indices);
    }

    void Draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
private:

};

