#include "Camera.h"
#include <algorithm>

Camera::Camera(const glm::vec3&& position) :
	position(position), pitch(0.0f), yaw(-glm::half_pi<float>())
{
	updateOrientation();
}

void Camera::updateOrientation()
{
	glm::vec3 front;
	front.x = cos(yaw) * cos(pitch);
	front.y = sin(pitch);
	front.z = sin(yaw) * cos(pitch);
	forward = glm::normalize(front);
	
	right = glm::normalize(glm::cross(front, DEFAULT_UP));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::translate(glm::vec3 offset)
{
	position += offset.x * right + offset.y * up + offset.z * forward;
}

void Camera::rotate(glm::vec2 angles)
{
	yaw += angles.x;
	if (yaw > glm::pi<float>())
	{
		yaw -= glm::two_pi<float>();
	}
	if (yaw <= -glm::pi<float>())
	{
		yaw += glm::two_pi<float>();
	}

	pitch = std::clamp(pitch + angles.y, -glm::half_pi<float>() + EPSILON, glm::half_pi<float>() - EPSILON);

	updateOrientation();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::getProjectionMatrix(float appAspect)
{
	return glm::perspective(FOV_Y, appAspect, NEAR_CLIP_PLANE, FAR_CLIP_PLANE);
}

glm::vec3 Camera::getPosition()
{
	return position;
}
