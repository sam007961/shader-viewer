#pragma once
#include "RigidBodyTransform.h"
#include "Material.h"
#include "Geometry.h"

class SceneObject {
protected:
	RigidBodyTransform rbt; // position and rotaion

public:

	SceneObject();
	void setPosition(glm::vec3 position);
	void setRotation(glm::quat rotation);
	void translate(glm::vec3 translation); // world frame translation
	void rotate(float angle, glm::vec3 axis); // object frame rotation | axis must be normalized
	void rotate(float angle, glm::vec3 center, glm::vec3 axis); // center frame rotation | axis aligned with object frame | axis located at center | axis must be normalized
	void orbit(float angle, glm::vec3 center, glm::vec3 axis); // center frame rotation | axis aligned with world frame  | axis located at center | axis must be normalized
	glm::mat4 makeModelMatrix() const;
};

template<typename GeometryType>
class DrawableObject : public SceneObject {
private:
	Material _material;
	GeometryType* _geometry;

public:
	DrawableObject() : SceneObject() {}
	void setGeometry(GeometryType* geometry) { _geometry = geometry; }
	void setMaterial(const Material& material) { _material = material; }
	Material material() const { return _material; }
	GeometryType* geometry() const { return _geometry; }
};