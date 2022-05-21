#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

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

struct LightSources
{
    static const int MAX_DIRECTIONAL_LIGHTS = 4;
    static const int MAX_POINT_LIGHTS = 8;

    AmbientLight ambient;

    DirectionalLight directional[MAX_DIRECTIONAL_LIGHTS]{ };
    int directionalCount;

    PointLight point[MAX_POINT_LIGHTS]{ };
    int pointCount;

    LightSources() :
        ambient(glm::vec3(0.0f, 0.0f, 0.0f)), directionalCount(0), pointCount(2)
    {
        //directional[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
        //directional[0].direction = glm::vec3(-0.6667f, 0.3333f, -0.6667f);

        //directional[1].color = glm::vec3(0.7f, 0.0f, 0.7f);
        //directional[1].direction = glm::vec3(0.6667f, 0.3333f, 0.6667f);

        point[0].color = glm::vec3(1.0f, 0.0f, 1.0f);
        point[0].position = glm::vec3(0.0f, 0.0f, -4.0f);

        point[1].color = glm::vec3(1.0f, 0.0f, 0.0f);
        point[1].position = glm::vec3(0.0f, 0.0f, 4.0f);
    }

    static size_t bufferSize()
    {
        return sizeof(LightSources);
    }
};