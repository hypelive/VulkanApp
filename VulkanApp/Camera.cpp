#include "Camera.h"

Camera::Camera(const glm::vec3&& position)
{
	this->position = position;
}

void Camera::translate(glm::vec3 offset)
{
	// TODO
	position += glm::rotate(glm::quat(glm::vec3(-rotation.y, rotation.x, 0.0f)), offset);
}

void Camera::rotate(glm::vec2 angles)
{
	rotation += angles;

	rotation.y = glm::clamp(rotation.y, -glm::half_pi<float>(), glm::half_pi<float>());
	
	if (rotation.x > glm::pi<float>())
	{
		rotation.x -= 2 * glm::pi<float>();
	}
	if (rotation.x < -glm::pi<float>())
	{
		rotation.x += 2 * glm::pi<float>();
	}
}

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 res = glm::rotate(glm::mat4(1.0f), -rotation.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	res = glm::rotate(res, rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
	res = glm::translate(res, -position);

	return res;
}
