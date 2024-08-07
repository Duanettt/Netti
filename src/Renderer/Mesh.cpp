#include "Mesh.h"

void Mesh::applyTranslate(glm::vec3 position)
{
    _model = glm::translate(_model, position);
}

void Mesh::applyRotate(glm::vec3 rotation, float deg)
{
    _model = glm::rotate(_model, glm::radians(deg), rotation);
}

void Mesh::applyScaling(glm::vec3 scale)
{
    _model = glm::scale(_model, scale);
}

void Mesh::applyGravity()
{
    physics.applyForce(glm::vec3(0.0f, -0.98f, 0.0f));

    glm::vec3 newPosition = physics.getPosition();

    _model = glm::translate(_model, newPosition);
}

void Mesh::updatePhysics(float& deltaTime)
{
    physics.update(deltaTime);

}

void Mesh::Draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Mesh::Draw(GLenum drawMode, GLsizei numOfIndices, GLenum indicesType)
{
    glBindVertexArray(VAO);
    glDrawElements(drawMode, numOfIndices, indicesType, 0);
    glBindVertexArray(0);
}

glm::mat4 Mesh::getModelMatrix()
{
    return Mesh::_model;
}

void Mesh::Transformations(Shader& ourShader)
{
    glm::mat4 model = getModelMatrix();
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
}

void Mesh::uploadVertexData(std::vector<Vertex> vertices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Mesh::uploadVertexData(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}
