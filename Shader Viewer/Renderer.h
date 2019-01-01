#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Geometry.h"

class Renderer {
private:
	GLProgram* program;
	unsigned int n_elements;

public:
	Renderer() : program(nullptr) {}

	void setProgram(GLProgram* program) { // set program
		assert(program != nullptr);
		assert((*program) > 0);

		this->program = program;
	}

	template<class GeometryType>
	void draw(GeometryType* target) { // draw geometry
		assert(program != nullptr);
		assert((*program) > 0);

		glUseProgram(*program);
		glBindVertexArray(*target);
		glDrawElements(GL_TRIANGLES, target->elementCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
};