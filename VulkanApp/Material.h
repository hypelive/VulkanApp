#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

struct MaterialProperties
{
	glm::vec3 F0;
	float alphaMaskingShadowing;
	float alphaNormalDistribution;

	MaterialProperties(glm::vec3 F0, float alphaMaskingShadowing, float alphaNormalDistribution) :
		F0(F0), alphaMaskingShadowing(alphaMaskingShadowing), alphaNormalDistribution(alphaNormalDistribution) { }
};