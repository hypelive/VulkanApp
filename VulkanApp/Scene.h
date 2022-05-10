#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

#include "Camera.h"
#include "LightSource.h"
#include "Material.h"
#include "ModelData.h"
#include "Vertex.h"

class Scene
{
public:
    Camera camera;
    LightSources lightSources;
    MaterialProperties material;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<ModelData> modelData;

    Scene();
};

