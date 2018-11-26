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

void Geometry::copyBuffers(const Vertex* vtx, unsigned short const* idx,
	int vboLen, int iboLen) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vboLen,
		vtx, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned short) * iboLen, idx, GL_STATIC_DRAW);
	this->iboLen = iboLen;
	this->vboLen = vboLen;
}
// buffer constructor
Geometry::Geometry(const Vertex* vtx, unsigned short const* idx,
	int vboLen, int iboLen) : Geometry() {
	copyBuffers(vtx, idx, vboLen, iboLen);
}

// destructor
Geometry::~Geometry() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

#define FIELD_OFFSET(StructType, field) &(((StructType *)0)->field)
// draw geometry using the specified shader
void Geometry::draw(const GLProgram& prog) const {
	const GLuint h_aPosition = prog.attr.at("aPosition");
	const GLuint h_aNormal = prog.attr.at("aNormal");
	glEnableVertexAttribArray(h_aPosition);
	glEnableVertexAttribArray(h_aNormal);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(h_aPosition, 3, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), FIELD_OFFSET(Vertex, pos));
	glVertexAttribPointer(h_aNormal, 3, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), FIELD_OFFSET(Vertex, normal));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, iboLen, GL_UNSIGNED_SHORT, 0);

}
#undef FIELD_OFFSET

// Load plane into buffers
void buildPlaneBuffers(const float& size, 
	Vertex* vtxIter, unsigned short* idxIter) {
	const float h = size / 2.0;
	*vtxIter     = Vertex(-h, 0, -h, 0, 1, 0, 0, 0);
	*(vtxIter + 1) = Vertex(-h, 0,  h, 0, 1, 0, 0, 1);
	*(vtxIter + 2) = Vertex( h, 0,  h, 0, 1, 0, 1, 1);
	*(vtxIter + 3) = Vertex( h, 0, -h, 0, 1, 0, 1, 0);

	*idxIter = 0;
	*(idxIter + 1) = 1;
	*(idxIter + 2) = 2;
	*(idxIter + 3) = 0;
	*(idxIter + 4) = 2;
	*(idxIter + 5) = 3;
}

Plane::Plane() : Plane(1.0f) {}

Plane::Plane(const float& size) : Geometry(){
	Vertex* vbuff = new Vertex[VBLEN_PLANE];
	unsigned short* ibuff = new unsigned short[IBLEN_PLANE];
	buildPlaneBuffers(size, vbuff, ibuff);
	copyBuffers(vbuff, ibuff, VBLEN_PLANE, IBLEN_PLANE);
}