#include <GL\glew.h>
#include <assert.h>
#include "VertexLayout.h"

Vertex::Vertex(
	float x, float y, float z,
	float nx, float ny, float nz,
	float tu, float tv)
	: position(x, y, z), normal(nx, ny, nz), tex(tu, tv) {}

VertexP::VertexP(Vertex v) {
	position = v.position;
}

void VertexP::enableAttributes(unsigned int i = 0) {
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(i++);
}

VertexPN::VertexPN(Vertex v) {
	position = v.position;
	normal = v.normal;
}

void VertexPN::enableAttributes(unsigned int i = 0) {
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 
		sizeof(VertexPN), (GLvoid*)offsetof(VertexPN, normal));
	glEnableVertexAttribArray(i++);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexPN), (GLvoid*)offsetof(VertexPN, normal));
	glEnableVertexAttribArray(i++);
}
// PROGRAM INPUT //////////////////////////////////////////////////////////////////////////////

VertexLayout::VertexLayout() {
	glGenVertexArrays(1, &handle);
}

VertexLayout::operator GLuint() const { return handle; }


VertexLayout::~VertexLayout() {
	glDeleteVertexArrays(1, &handle);
}
