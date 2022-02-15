#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/scalar_constants.hpp>


// TODO transform component
class Camera
{
	glm::vec3 position;

	glm::vec3 forward;
	glm::vec3 up;
	// store or compute right?

public:
	Camera(const glm::vec3&& position);

	void translate(glm::vec3 offset);
	void rotate(glm::vec2 angles);

	glm::mat4 getViewMatrix();
};

