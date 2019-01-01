#pragma once
#include <glm/glm.hpp>
//#include <glm/>

class SceneObject {
protected:
	using vec3 = glm::vec3;
	using quat = glm::quat;
	using mat4 = glm::mat4;

	// rigid body transformation
	vec3 translation;
	quat rotaion;
};