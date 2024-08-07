#include "Physics.h"

void Physics::applyForce(const glm::vec3& force)
{
	acceleration += force / mass;
}

void Physics::update(float deltaTime)
{
	velocity += acceleration * deltaTime;

	position += velocity * deltaTime + 0.5f * acceleration * deltaTime * deltaTime;

	acceleration = glm::vec3(0.0f);
}

void Physics::setPosition(glm::vec3& pos)
{
	position = pos;
}

glm::vec3 Physics::getPosition() const
{
	return position;
}

void Physics::setAcceleration(glm::vec3& accel)
{
	acceleration = accel;
}

void Physics::setVelocity(glm::vec3& velo)
{
	velocity = velo;
}

void Physics::setMass(float& m)
{
	mass = m;
}
