#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Geometry.h"
#include "Texture.h"
#include "Framebuffer.h"

class Renderer {
private:
	GLProgram* program;
	unsigned int n_elements;

public:
	Renderer() {}

	void setProgram(GLProgram* program) { // set program
		assert((*program) > 0);
		this->program = program;
	}

	void setProgram(std::shared_ptr<GLProgram> program) { // set program
		assert((*program) > 0);
		this->program = program.get();
	}

	template<class GeometryType>
	void draw(const GeometryType& target, GLenum mode=GL_TRIANGLES) const { // draw geometry
		assert((*program) > 0);

		glUseProgram(*program);
		glBindVertexArray(target);
		glDrawElements(mode, target.elementCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	template<class GeometryType>
	void draw(const GeometryType& target, const GLFramebuffer& fbo, GLenum mode=GL_TRIANGLES) const { // draw geometry to specific fbo
		assert(program != nullptr);
		assert((*program) > 0);

		glUseProgram(*program);
		glBindVertexArray(target);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glDrawElements(mode, target.elementCount(), GL_UNSIGNED_INT, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
};