#pragma once

#include "MeshData.h"
#include "Transform.h"

class SceneObject
{
public:
	uint32_t id;
	Transform transform;
	MeshData meshData;

	SceneObject();
	SceneObject(uint32_t id, Transform transform, MeshData meshData);
};

