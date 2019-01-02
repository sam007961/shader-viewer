#pragma once
#include "Scene.h"

class Camera : public SceneObject {
private:
	glm::mat4 projMatrix;

public:
	Camera();

	void lookAt(glm::vec3 at);
	void setProjection(float yfov, float aspect, float znear, float zfar);

	glm::mat4 makeViewMatrix() const;
	glm::mat4 makeProjMatrix() const;

	
};