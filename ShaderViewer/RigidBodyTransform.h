#pragma once
#include <glm/common.hpp>	
#include <glm/gtc/quaternion.hpp>

struct RigidBodyTransform {
	glm::vec3 translation;
	glm::quat rotation;

	RigidBodyTransform();
	RigidBodyTransform(glm::vec3 translation, glm::quat rotaion);
	RigidBodyTransform operator*(const RigidBodyTransform& other) const;
	//RigidBodyTransform& operator=(const RigidBodyTransform& other);
	RigidBodyTransform inv() const;
	RigidBodyTransform tranlational() const;
	RigidBodyTransform rotational() const;

	glm::mat4 toMat4() const;

	static RigidBodyTransform makeRotation(float angle, glm::vec3 axis);
	static RigidBodyTransform makeTranslation(glm::vec3 translation);
};