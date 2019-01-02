#pragma once
#include <glm/gtc/quaternion.hpp>

struct RigidBodyTransform {
	using vec3 = glm::vec3;
	using quat = glm::quat;
	using mat4 = glm::mat4;

	vec3 translation;
	quat rotation;

	RigidBodyTransform();
	RigidBodyTransform(vec3 translation, quat rotaion);
	RigidBodyTransform operator*(const RigidBodyTransform& other) const;
	RigidBodyTransform inv() const;
	mat4 toMat4() const;
};