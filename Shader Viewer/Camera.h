#pragma once
#include "Scene.h"

class Camera : public SceneObject {
	using vec3 = glm::vec3;
	using mat4 = glm::mat4;
private:
	mat4 projMatrix;	

public:
	Camera();

	void lookAt(vec3 origin, vec3 center, vec3 vup);
	void setProjection(float yfov, float aspect, float znear, float zfar);

	inline mat4 makeViewMatrix() const;
	inline mat4 makeProjMatrix() const;
};