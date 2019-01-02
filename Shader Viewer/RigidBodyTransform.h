#pragma once
#include <glm/common.hpp>	
#include <glm/gtc/quaternion.hpp>

struct RigidBodyTransform {
	glm::vec3 translation;
	glm::quat rotation;

	RigidBodyTransform();
	RigidBodyTransform(glm::vec3 translation, glm::quat rotaion);
	RigidBodyTransform operator*(const RigidBodyTransform& other) const;
	RigidBodyTransform inv() const;
	glm::mat4 toMat4() const;
};