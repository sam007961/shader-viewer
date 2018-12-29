#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"


class Renderer {
private:
	GLProgram* program;
	VertexLayout* layout;
	unsigned int n_elements;

public:
	Renderer();

	void setProgram(GLProgram* program); // set program
	void setVertexLayout(VertexLayout* layout);
	void setElementCount(unsigned int n_elements);
	void draw();
};