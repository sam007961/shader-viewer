#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() : layout(nullptr), program(nullptr), n_elements(0) {}

void Renderer::setProgram(GLProgram* program) {
	assert(program != nullptr);
	assert((*program) > 0);

	this->program = program;
}

void Renderer::setVertexLayout(VertexLayout* layout) {
	this->layout = layout;
}

void Renderer::draw() {
	assert(program != nullptr);
	assert((*program) > 0);

	glUseProgram(*program);
	glBindVertexArray(*layout);

	glDrawElements(GL_TRIANGLES, layout->getNumElem() , GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

