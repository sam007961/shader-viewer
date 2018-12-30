#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() : program(nullptr) {}

void Renderer::setProgram(GLProgram* program) {
	assert(program != nullptr);
	assert((*program) > 0);

	this->program = program;
}
