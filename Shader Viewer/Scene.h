#pragma once
#include "RigidBodyTransform.h"

class SceneObject {
protected:
	RigidBodyTransform rbt; // position and rotaion

public:

	SceneObject();
	void setPosition(glm::vec3 position);
	void setRotation(glm::quat rotation);
	void translate(glm::vec3 translation); // world frame translation
	void rotate(float angle, glm::vec3 axis); // object frame rotation | axis must be normalized

	glm::mat4 makeModelMatrix() const;
};

class DrawableObject : public SceneObject {
	// TODO
};