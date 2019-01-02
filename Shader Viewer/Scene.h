#pragma once
#include "RigidBodyTransform.h"

class SceneObject {
	using vec3 = glm::vec3;
	using quat = glm::quat;
	using mat4 = glm::mat4;

protected:
	RigidBodyTransform rbt; // position and rotaion

public:
	SceneObject();
	void setPosition(vec3 position);
	void setRotation(quat rotation);
	void translate(vec3 translation); // world frame translation
	void rotate(vec3 axis, float angle); // object frame rotation

	inline mat4 makeModelMatrix() const;
};

class DrawableObject : public SceneObject {
	// TODO
};