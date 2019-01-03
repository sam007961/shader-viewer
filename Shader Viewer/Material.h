#pragma once
#include <glm/common.hpp>

struct Material {
	glm::vec3 color;
	glm::vec3 ambient;

	Material() {}
	Material(glm::vec3 color, glm::vec3 ambient)
		: color(color), ambient(ambient) {}
};