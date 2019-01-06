#include <cmath>
#include "Scene.h"

SceneObject::SceneObject() {}

void SceneObject::setPosition(glm::vec3 position) { rbt.translation = position; }
void SceneObject::setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }

void SceneObject::setRotation(glm::quat rotation) { rbt.rotation = glm::normalize(rotation); }
void SceneObject::setRotation(float w, float x, float y, float z) { setRotation(glm::quat(w, x, y, z)); }

void SceneObject::translate(glm::vec3 translation) { rbt.translation += translation; }
void SceneObject::translate(float x, float y, float z) { translate(glm::vec3(x, y, z)); }

void SceneObject::rotate(float angle, glm::vec3 axis) {
	RigidBodyTransform rbt_rotation = RigidBodyTransform::makeRotation(angle, axis);
	rbt = rbt * rbt_rotation;
}

void SceneObject::rotate(float angle, glm::vec3 center, glm::vec3 axis) {
	RigidBodyTransform center_rbt = RigidBodyTransform::makeTranslation(center);
	RigidBodyTransform rbt_rotation = RigidBodyTransform::makeRotation(angle, axis);
	rbt = center_rbt * rbt_rotation * center_rbt.inv() * rbt;
}

void SceneObject::orbit(float angle, glm::vec3 center, glm::vec3 axis) {
	RigidBodyTransform center_rbt =
		RigidBodyTransform::makeTranslation(center) * rbt.rotational();
	RigidBodyTransform rbt_rotation = RigidBodyTransform::makeRotation(angle, axis);
	rbt = center_rbt * rbt_rotation * center_rbt.inv() * rbt;
}

glm::mat4 SceneObject::makeModelMatrix() const { return rbt.toMat4(); }