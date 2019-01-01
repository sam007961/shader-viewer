#pragma once
#include "Scene.h"

class Camera : public SceneObject {
private:
	

public:
	Camera();
	Camera(mat4 viewMatrix, mat4 projMatrix);
	Camera(
		vec3 origin, vec3 center, vec3 vup,
		double yfov, double aspect,
		double znear, double zfar
	);

	void setPosition(vec3 position);
	void setRotation(quat rotation);

	void translate(vec3 translation);
	void rotate(vec3 axis, double angle);


	inline mat4 makeViewMatrix() const;
	inline mat4 makeProjMatrix() const;
};