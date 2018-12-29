#include <GL\glew.h>
#include <assert.h>
#include "VertexLayout.h"

// PROGRAM INPUT //////////////////////////////////////////////////////////////////////////////

VertexLayout::VertexLayout(unsigned int n_buffers) : n_buffers(n_buffers), n_elements(0) {
	// generate buffers
	vbo = new GLuint[n_buffers];
	glGenBuffers(n_buffers, vbo);

	// generate vertex array object
	glGenVertexArrays(1, &handle);
	glBindVertexArray(handle);

	// positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

void VertexLayout::bufferData(unsigned int index, void* buff, size_t size) {
	assert(index < n_buffers);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
	glBufferData(GL_ARRAY_BUFFER, size,
		buff, GL_STATIC_DRAW);
}

VertexLayout::operator GLuint() const {
	return handle;
}


VertexLayout::~VertexLayout() {
	glDeleteBuffers(n_buffers, vbo);
	glDeleteVertexArrays(1, &handle);
}
