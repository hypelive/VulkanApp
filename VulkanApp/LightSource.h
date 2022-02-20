#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

enum LightSourceType : int8_t
{
	AMBIENT = 0,
	DIRECTIONAL = 1,
	POINT = 2,
};

struct LightSource
{
	LightSourceType type;
	glm::vec3 color;
	
	LightSource(LightSourceType lightType, glm::vec3 lightColor) : type(lightType), color(lightColor) { };
};

struct AmbientLight : LightSource
{
	AmbientLight(glm::vec3 lightColor) : LightSource(AMBIENT, lightColor) { }
};

struct DirectionalLight : LightSource
{
	glm::vec3 direction;

	DirectionalLight(glm::vec3 lightColor, glm::vec3 lightDirection) : LightSource(DIRECTIONAL, lightColor), direction(lightDirection) { }
};

struct PointLight : LightSource
{
	float radius;

	PointLight(glm::vec3 lightColor, float lightRadius) : LightSource(POINT, lightColor), radius(lightRadius) { }
};