#pragma once
#include <GL\glew.h>
#include <glm/common.hpp>

#define MAT_MAX_TEXTURES 16

struct Material {
	glm::vec3 color;
	glm::vec3 ambient;
	GLuint textures[MAT_MAX_TEXTURES];

	Material() {}
	Material(glm::vec3 color, glm::vec3 ambient)
		: color(color), ambient(ambient) {}
};