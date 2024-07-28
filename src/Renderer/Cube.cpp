#include "Cube.h"

void Cube::Draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::applyTranslate(glm::vec3 position)
{

    _model = glm::translate(_model, position);
}

void Cube::applyRotate(glm::vec3 rotation, float deg)
{

    _model = glm::rotate(_model, glm::radians(deg), rotation);
}

void Cube::applyScaling(glm::vec3 scale)
{

    _model = glm::scale(_model, scale);
}


glm::mat4 Cube::getModelMatrix()
{
    return Cube::_model;
}

void Cube::Transformations(Shader& ourShader)
{
    glm::mat4 model = getModelMatrix();
    // make sure to initialize matrix to identity matrix first
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

}

void Cube::uploadVertexData()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}
