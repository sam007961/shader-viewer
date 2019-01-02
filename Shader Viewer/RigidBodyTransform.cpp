#include <glm/gtc/matrix_transform.hpp>
#include "RigidBodyTransform.h"

RigidBodyTransform::RigidBodyTransform(glm::vec3 translation, glm::quat rotaion)
	: translation(translation), rotation(rotaion) {}

RigidBodyTransform RigidBodyTransform::operator*(const RigidBodyTransform& other) const {
	return RigidBodyTransform(
		translation + rotation * other.translation,
		rotation * other.rotation
	);
}

RigidBodyTransform RigidBodyTransform::inv() const {
	glm::quat qinv = glm::inverse(rotation);
	return RigidBodyTransform(-qinv * translation, qinv);
}

glm::mat4 RigidBodyTransform::toMat4() const {
	return glm::translate(glm::mat4(1), translation) * glm::mat4_cast(rotation);
}