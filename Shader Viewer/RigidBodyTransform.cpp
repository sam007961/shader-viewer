#include <glm/gtc/matrix_transform.hpp>
#include "RigidBodyTransform.h"

using vec3 = glm::vec3;
using quat = glm::quat;
using mat4 = glm::mat4;

RigidBodyTransform::RigidBodyTransform() {}
RigidBodyTransform::RigidBodyTransform(vec3 translation, quat rotaion)
	: translation(translation), rotation(rotaion) {}

RigidBodyTransform RigidBodyTransform::operator*(const RigidBodyTransform& other) const {
	return RigidBodyTransform(
		translation + rotation * other.translation,
		rotation * other.rotation
	);
}

RigidBodyTransform RigidBodyTransform::inv() const {
	quat qinv = glm::inverse(rotation);
	return RigidBodyTransform(-qinv * translation, qinv);
}

mat4 RigidBodyTransform::toMat4() const {
	return glm::translate(mat4(1), translation) * glm::mat4_cast(rotation);
}