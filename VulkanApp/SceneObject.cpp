#include "SceneObject.h"

SceneObject::SceneObject() :
	id(),
	transform(),
	meshData(),
	material() { }

SceneObject::SceneObject(uint32_t id, Transform transform, MeshData meshData, MaterialProperties material) :
	id(id), transform(transform), meshData(meshData), material(material) { }
