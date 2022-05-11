#include "Transform.h"

Transform::Transform() :
	position(glm::vec3(0.0f, 0.0f, 0.0f)),
	rotation(glm::quat(0.0f, 0.0f, 0.0f, 1.0f)),
	scale(glm::vec3(1.0f, 1.0f, 1.0f)) { }

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) :
	position(position), rotation(rotation), scale(scale) { }

glm::mat4 Transform::GetMatrix()
{
	return glm::translate(glm::toMat4(rotation) * glm::scale(glm::identity<glm::mat4>(), scale), position);
}
