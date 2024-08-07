#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class Physics
{
public:

	Physics() : position(0.0f), velocity(0.0f), acceleration(0.0f), mass(1.0f) 
	{
	}

	// Force = mass x acceleration, 
	void applyForce(const glm::vec3& force);

	// Updates the physics with delta time.
	void update(float deltaTime);

	// Sets position over and over again.
	void setPosition(glm::vec3& pos);

	glm::vec3 getPosition() const;

	void setAcceleration(glm::vec3& accel);

	void setVelocity(glm::vec3& velo);

	void setMass(float& m);
private:
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 position;

	float mass;
	
};

