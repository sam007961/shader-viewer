#pragma once
#include "Shader.h"
#include "Geometry.h"

class Drawer {
private:
	const GLTarget* target;
	const GLProgram* prog;
public:
	Drawer();
	Drawer(const GLTarget* target);
	Drawer(const GLProgram* prog);
	Drawer(const GLTarget* target, const GLProgram* prog);
	virtual void setTarget(const GLTarget* target);
	virtual void setProgram(const GLProgram* prog);
	virtual void draw(const Geometry& geom) const = 0;

};



#define FIELD_OFFSET(StructType, field) &(((StructType *)0)->field)


// draw geometry using the specified shader
void draw(const GLProgram& prog) {
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