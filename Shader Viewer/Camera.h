#pragma once
#include "Scene.h"

class Camera : public SceneObject {
private:
	glm::mat4 projMatrix;

public:
	Camera();

	void lookAt(glm::vec3 at);
	void lookAt(float x, float y, float z);
	void perspective(float yfov, float aspect, 
		float znear=0.01f, float zfar=100.0f);
	void orthogonal(float left, float right, float bottom, float top, 
		float znear=0.01f, float zfar=100.0f);

	glm::mat4 makeViewMatrix() const;
	glm::mat4 makeProjMatrix() const;

	
};