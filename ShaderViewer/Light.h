#pragma once
#include "Camera.h"

class Light : public Camera {
public:
	Light();
	virtual operator glm::vec3() const = 0;
	glm::mat4 makeLightSpaceMatrix();
};

class PointLight : public Light {
public:
	PointLight();
	PointLight(float x, float y, float z);
	virtual operator glm::vec3() const;
};

class DirectionalLight : public Light {
public:
	DirectionalLight();
	DirectionalLight(float x, float y, float z);
	void setDirection(float x, float y, float z);
	virtual operator glm::vec3() const;
};