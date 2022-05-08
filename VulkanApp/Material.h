#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

struct MaterialProperties
{
	glm::vec3 F0;
	float alpha;

	MaterialProperties(glm::vec3 F0, float alpha) :
		F0(F0), alpha(alpha) { }
};