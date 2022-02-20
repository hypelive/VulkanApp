#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// will be removed
enum LightSourceType : int8_t
{
	AMBIENT = 0,
	DIRECTIONAL = 1,
	POINT = 2,
};

struct LightSource
{
	glm::vec3 color;
	
	LightSource() { }

	LightSource(glm::vec3 lightColor) :
		color(lightColor) { };
};

struct AmbientLight : LightSource
{
	AmbientLight() { }

	AmbientLight(glm::vec3 lightColor) :
		LightSource(lightColor) { }
};

struct DirectionalLight : LightSource
{
	glm::vec3 direction;

	DirectionalLight() { }

	DirectionalLight(glm::vec3 lightColor, glm::vec3 lightDirection) :
		LightSource(lightColor), direction(lightDirection) { }
};

struct PointLight : LightSource
{
	glm::vec3 position;

	PointLight() { }

	PointLight(glm::vec3 lightColor, glm::vec3 lightPosition) :
		LightSource(lightColor), position(lightPosition) { }
};