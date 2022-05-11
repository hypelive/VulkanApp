#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/ext/scalar_constants.hpp>

class Transform
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	Transform();
	Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

	glm::mat4 GetMatrix();
};

