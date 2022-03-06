#include "Camera.h"

Camera::Camera(const glm::vec3&& position)
{
	this->position = position;

	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::translate(glm::vec3 offset)
{
	glm::vec3 right = glm::cross(forward, up);

	position += offset.x * right + offset.y * up + offset.z * forward;
}

void Camera::rotate(glm::vec2 angles)
{
	forward = glm::rotate(forward, angles.x, up);

	glm::vec3 right = glm::cross(forward, up);
	up = glm::rotate(up, angles.y, right);
	forward = glm::rotate(forward, angles.y, right);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}

glm::vec3 Camera::getPosition()
{
	return position;
}
