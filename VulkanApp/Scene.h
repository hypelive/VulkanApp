#pragma once
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "Camera.h"
#include "LightSource.h"
#include "Material.h"
#include "Vertex.h"
#include "SceneObject.h"

class Scene
{
public:
    Camera camera;
    LightSources lightSources;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<SceneObject> sceneObjects;

    Scene();
};

