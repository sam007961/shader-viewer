#include <cmath>
#include "Scene.h"

SceneObject::SceneObject() {}

void SceneObject::setPosition(glm::vec3 position) { rbt.translation = position; }
void SceneObject::setRotation(glm::quat rotation) { rbt.rotation = glm::normalize(rotation); }
void SceneObject::translate(glm::vec3 translation) { rbt.translation += translation; }
void SceneObject::rotate(float angle, glm::vec3 axis) {
	rbt.rotation = rbt.rotation * glm::angleAxis(angle, axis);
}
glm::mat4 SceneObject::makeModelMatrix() const { return rbt.toMat4(); }