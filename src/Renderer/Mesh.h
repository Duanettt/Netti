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
#include "../Physics/Physics.h"


class Mesh
{
public:
	unsigned int VAO, VBO, EBO;
	std::string name;
	// Some modern compilres can give an error about having virtual functions and an accessible non-virtual destructor.
	virtual ~Mesh() = default;

	glm::vec3 position = glm::vec3(0.0f);

	glm::mat4 _model = glm::mat4(1.0f);

	Physics physics;

	Mesh(const std::string &name) : name(name)
	{

	}

	Mesh(const std::string& name, std::vector<Vertex> vertices) : name(name)
	{
		uploadVertexData(vertices);
	}

	Mesh(const std::string& name, std::vector<Vertex> vertices, std::vector<unsigned int> indices) : name(name)
	{
		uploadVertexData(vertices, indices);
	}

	void applyTranslate(glm::vec3 position);

	void applyRotate(glm::vec3 rotation, float deg);

	void applyScaling(glm::vec3 scale);

	void applyGravity();

	void updatePhysics(float& deltaTime);
	
	void Draw();

	void Draw(GLenum drawMode, GLsizei numOfIndices, GLenum indicesType);

	glm::mat4 getModelMatrix();

	glm::vec3 getPosition();

	void Transformations(Shader& ourShader);


	void uploadVertexData(std::vector<Vertex> vertices);

	void uploadVertexData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

private:
};

