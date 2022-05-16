#pragma once

#include "MeshData.h"
#include "Transform.h"
#include "Material.h"

class SceneObject
{
public:
	uint32_t id;
	Transform transform;
	MeshData meshData;
	MaterialProperties material;

	SceneObject();
	SceneObject(uint32_t id, Transform transform, MeshData meshData, MaterialProperties material);
};

