#include "Renderer.h"



void Renderer::RunEvents()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

unsigned int Renderer::CreateVAO(const float* vertices, size_t verticesSize, const unsigned int* indices, size_t indicesSize, int multiplier)
{

    for (size_t i = 0; i < indicesSize / sizeof(float); ++i) {
        std::cout << "Element " << i << ": " << indices[i] << std::endl;
    }

    unsigned int VBO, VAO, EBO;

    // Generate and bind Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Generate and bind Element Buffer Object
     glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
 
    std::cout << "Generated vertex arrays, vertex buffer objects and elemental buffer objects" << std::endl; 

    // Set vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, multiplier * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return VAO;
}


unsigned int Renderer::CreateVAO(const float* vertices, size_t verticesSize, int multiplier)
{

    unsigned int VBO, VAO;

    // Generate and bind Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

    // Generate and bind Element Buffer Object

    std::cout << "Generated vertex arrays, vertex buffer objects and elemental buffer objects" << std::endl;

    // Set vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute/Texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, multiplier * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}


unsigned int Renderer::LoadTexture(const char* path, GLenum format)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load textures";
    }

    stbi_image_free(data); 

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;

}


void Renderer::Render(Shader ourShader, unsigned int& VAO, unsigned int& texture)
{
    glClearColor(0.17f, 0.17f, 0.17f, 0.17f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render your objects here
/*    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); */

    ourShader.use();
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


}

void Renderer::Render(Shader ourShader, Mesh& mesh, unsigned int& texture1, unsigned int texture2, int screenHeight, int screenWidth, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
    glClearColor(0.17f, 0.17f, 0.17f, 0.17f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);


    // View matrix - Transforms vertex coordinates from world space to camera/view space using the view matrix

    glm::mat4 view;
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


    // Transforms vertex coordinates from view space to clipping space.
    glm::mat4 projection = glm::mat4(1.0f);
    // We divide 800/600 to keep the same aspect ratio for each vertex coordinate reducing improportions.
    projection = glm::perspective(glm::radians(45.0f), (float)screenHeight / (float)screenWidth, 0.1f, 100.0f);

    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);

    ourShader.use();

    mesh.Transformations(ourShader);
    mesh.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT);


}


void Renderer::Render(Shader ourShader, std::vector<Mesh> meshes, unsigned int& texture1, unsigned int texture2, int screenHeight, int screenWidth, Camera& camera)
{
    glClearColor(0.17f, 0.17f, 0.17f, 0.17f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);


    // View matrix - Transforms vertex coordinates from world space to camera/view space using the view matrix
    glm::mat4 view;
    view = camera.GetViewMatrix();

    // Transforms vertex coordinates from view space to clipping space.
    glm::mat4 projection = glm::mat4(1.0f);
    // We divide 800/600 to keep the same aspect ratio for each vertex coordinate reducing improportions.
    projection = glm::perspective(glm::radians(45.0f), (float)screenHeight / (float)screenWidth, 0.1f, 100.0f);

    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);

    ourShader.use();


    for (Mesh& mesh : meshes)
    {
        mesh.Transformations(ourShader);
        mesh.Draw();
    }


}