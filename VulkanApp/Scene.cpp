#include "Scene.h"

Scene::Scene() :
    camera(glm::vec3(0.0f, 0.0f, -5.0f)),
    lightSources(),
    material(glm::vec3(0.3f, 0.4f, 0.5f), 0.1f) { }
