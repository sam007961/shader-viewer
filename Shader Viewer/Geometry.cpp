#include "Geometry.h"

// default constructor
Geometry::Geometry() {
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
}

// copy constructor
Geometry::Geometry(const Geometry& g) {
	// copy buffer length
	vboLen = g.vboLen;
	iboLen = g.iboLen;

	// copy vertex buffer
	glBindBuffer(GL_COPY_READ_BUFFER, g.vbo);
	glBindBuffer(GL_COPY_WRITE_BUFFER, vbo);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,
		0, 0, sizeof(Vertex) * vboLen);


	// copy index buffer
	glBindBuffer(GL_COPY_READ_BUFFER, g.ibo);
	glBindBuffer(GL_COPY_WRITE_BUFFER, ibo);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,
		0, 0, sizeof(unsigned short) * iboLen);
}

// buffer constructor
Geometry::Geometry(const Vertex* vtx, unsigned short const* idx,
	int vboLen, int iboLen) : Geometry() {

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vboLen,
		vtx, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned short) * iboLen, idx, GL_STATIC_DRAW);
	this->iboLen = iboLen;
	this->vboLen = vboLen;
}

// destructor
Geometry::~Geometry() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

// Load plane into buffers
Geometry* Geometry::buildPlane(float size) {
	Vertex* vtxIter; unsigned short* idxIter;
	const float h = size / 2.0;
	*vtxIter       = Vertex(-h, 0, -h, 0, 1, 0, 0, 0);
	*(vtxIter + 1) = Vertex(-h, 0,  h, 0, 1, 0, 0, 1);
	*(vtxIter + 2) = Vertex( h, 0,  h, 0, 1, 0, 1, 1);
	*(vtxIter + 3) = Vertex( h, 0, -h, 0, 1, 0, 1, 0);

	*idxIter       = 0;
	*(idxIter + 1) = 1;
	*(idxIter + 2) = 2;
	*(idxIter + 3) = 0;
	*(idxIter + 4) = 2;
	*(idxIter + 5) = 3;

	return new Geometry(vtxIter, idxIter, VBLEN_PLANE, IBLEN_PLANE);
}