#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/scalar_constants.hpp>

class Camera
{
	glm::vec3 position;

	float pitch;
	float yaw;

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

	const glm::vec3 DEFAULT_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	const float EPSILON = glm::pi<float>() / 180.0f;
	const float FOV_Y = glm::radians(40.0f);
	const float NEAR_CLIP_PLANE = 0.1f;
	const float FAR_CLIP_PLANE = 1000.0f;

	void updateOrientation();

public:
	Camera(const glm::vec3&& position);

	void translate(glm::vec3 offset);
	void rotate(glm::vec2 angles);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float appAspect);
	glm::vec3 getPosition();
};

