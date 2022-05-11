#include "SceneObject.h"

SceneObject::SceneObject() :
	id(0),
	transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f)),
	meshData() { }

SceneObject::SceneObject(uint32_t id, Transform transform, MeshData meshData) :
	id(id), transform(transform), meshData(meshData) { }
