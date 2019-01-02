#include <cmath>
#include "Scene.h"

using vec3 = glm::vec3;
using quat = glm::quat;
using mat4 = glm::mat4;

SceneObject::SceneObject() {}

void SceneObject::setPosition(vec3 position) { rbt.translation = position; }
void SceneObject::setRotation(quat rotation) { rbt.rotation = glm::normalize(rotation); }
void SceneObject::translate(vec3 translation) { rbt.translation += translation; }
void SceneObject::rotate(vec3 axis, float angle) { 
	RigidBodyTransform rbt_rot(vec3(0), glm::angleAxis(angle, glm::normalize(axis)));
	rbt = rbt * rbt_rot;
}
mat4 SceneObject::makeModelMatrix() const { return rbt.toMat4(); }