#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "utils/Data.h"
#include "Shader.h"


class Mesh
{
public:
	unsigned int VAO, VBO, EBO;
	// Some modern compilres can give an error about having virtual functions and an accessible non-virtual destructor.
	virtual ~Mesh() = default;

	glm::mat4 _model = glm::mat4(1.0f);

	Mesh()
	{

	}

	Mesh(std::vector<Vertex> vertices)
	{
		uploadVertexData(vertices);
	}

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		uploadVertexData(vertices, indices);
	}

	void applyTranslate(glm::vec3 position);

	void applyRotate(glm::vec3 rotation, float deg);

	void applyScaling(glm::vec3 scale);

	void Draw();

	void Draw(GLenum drawMode, GLsizei numOfIndices, GLenum indicesType);

	glm::mat4 getModelMatrix();

	void Transformations(Shader& ourShader);


	void uploadVertexData(std::vector<Vertex> vertices);

	void uploadVertexData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

private:
};

