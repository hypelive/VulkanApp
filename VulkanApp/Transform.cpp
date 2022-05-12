#include "Transform.h"

Transform::Transform() :
	position(glm::zero<glm::vec3>()),
	rotation(glm::identity<glm::quat>()),
	scale(glm::one<glm::vec3>()) { }

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale) :
	position(position), rotation(rotation), scale(scale) { }

glm::mat4 Transform::GetMatrix()
{
	return glm::translate(glm::toMat4(rotation) * glm::scale(glm::identity<glm::mat4>(), scale), position);
}
