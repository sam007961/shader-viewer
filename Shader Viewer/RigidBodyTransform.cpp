#include <glm/gtc/matrix_transform.hpp>
#include "RigidBodyTransform.h"

RigidBodyTransform::RigidBodyTransform() : translation(0), rotation(1, 0, 0, 0) {}
RigidBodyTransform::RigidBodyTransform(glm::vec3 translation, glm::quat rotaion)
	: translation(translation), rotation(rotaion) {}

RigidBodyTransform RigidBodyTransform::operator*(const RigidBodyTransform& other) const {
	return RigidBodyTransform(
		translation + rotation * other.translation,
		rotation * other.rotation
	);
}
//RigidBodyTransform& RigidBodyTransform::operator=(const RigidBodyTransform& other) {
//	translation = other.translation;
//	rotation = other.rotation;
//	return (*this);
//}

RigidBodyTransform RigidBodyTransform::inv() const {
	glm::quat qinv = glm::inverse(rotation);
	return RigidBodyTransform(-(qinv * translation), qinv);
}

glm::mat4 RigidBodyTransform::toMat4() const {
	auto temp = glm::translate(glm::mat4(1), translation) * glm::mat4_cast(rotation);
	return glm::translate(glm::mat4(1), translation) * glm::mat4_cast(rotation);
}

RigidBodyTransform RigidBodyTransform::tranlational() const {
	return RigidBodyTransform(translation, glm::quat(1, 0, 0, 0));
}

RigidBodyTransform RigidBodyTransform::rotational() const {
	return RigidBodyTransform(glm::vec3(0, 0, 0), rotation);
}

RigidBodyTransform RigidBodyTransform::makeRotation(float angle, glm::vec3 axis) {
	return RigidBodyTransform(glm::vec3(0, 0, 0), glm::angleAxis(angle, axis));
}

RigidBodyTransform RigidBodyTransform::makeTranslation(glm::vec3 translation) {
	return RigidBodyTransform(translation, glm::quat(1, 0, 0, 0));
}