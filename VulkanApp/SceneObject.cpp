#include "SceneObject.h"

SceneObject::SceneObject() :
	id(),
	transform(),
	meshData() { }

SceneObject::SceneObject(uint32_t id, Transform transform, MeshData meshData) :
	id(id), transform(transform), meshData(meshData) { }
