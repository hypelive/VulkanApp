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
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	glm::vec3 position;

	//glm::quat rotation;
	//glm::vec3 direction;
	glm::vec2 rotation;

	Camera(const glm::vec3&& position);

	void translate(glm::vec3 offset);
	void rotate(glm::vec2 angles);

	glm::mat4 getViewMatrix();
};

