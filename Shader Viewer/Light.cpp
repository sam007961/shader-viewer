#include "Light.h"

Light::Light() { /*ortho*/ }
glm::mat4 Light::makeLightMatrix() { return makeProjMatrix() * makeViewMatrix(); }

PointLight::PointLight() : Light() {}
PointLight::PointLight(float x, float y, float z) : Light() { setPosition(x, y, z); }
PointLight::operator glm::vec3() const { return rbt.translation; }

DirectionalLight::DirectionalLight() : Light() {}
DirectionalLight::DirectionalLight(float x, float y, float z) : Light() { lookAt(x, y, z); }
void DirectionalLight::setDirection(float x, float y, float z) {
	glm::vec3 position = rbt.translation;
	setPosition(0, 0, 0);
	lookAt(x, y, z);
	setPosition(position);
}
DirectionalLight::operator glm::vec3() const { return rbt.rotation * (-ZAXIS); }
