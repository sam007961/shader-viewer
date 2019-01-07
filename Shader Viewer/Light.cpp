#include "Light.h"

Light::Light() {}

// TODO cubemap for point light
PointLight::PointLight() : Light() { orthogonal(-10.0f, 10.0f, -10.0f, 10.0f); }
PointLight::PointLight(float x, float y, float z) : Light() { setPosition(x, y, z); }
PointLight::operator glm::vec3() const { return rbt.translation; }

DirectionalLight::DirectionalLight() : Light() { orthogonal(-10.0f, 10.0f, -10.0f, 10.0f); }
DirectionalLight::DirectionalLight(float x, float y, float z) : Light() { lookAt(x, y, z); }
void DirectionalLight::setDirection(float x, float y, float z) {
	glm::vec3 position = rbt.translation;
	setPosition(0, 0, 0);
	lookAt(x, y, z);
	setPosition(position);
}
DirectionalLight::operator glm::vec3() const { return rbt.rotation * (-ZAXIS); }
