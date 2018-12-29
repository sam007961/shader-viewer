#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Constants.h"

// Generic Vertex structure
struct Vertex {
	glm::vec3 pos;      // position
	glm::vec3 normal;   // normal
	glm::vec2 tex;      // uv-coordiantes

	Vertex() {}

	Vertex(
		float x, float y, float z,
		float nx, float ny, float nz,
		float tu, float tv)
		: pos(x, y, z), normal(nx, ny, nz), tex(tu, tv)
	{}
};

// Geometry class
struct Geometry {
	GLuint vbo, ibo;                      // vertex and index buffer object handles
	int vboLen, iboLen;                   // length of buffers

	Geometry();                           // generate vbo and ibo
	Geometry(const Geometry&);            // copy geometry
	Geometry(const Vertex*, 
		unsigned short const*, int, int); // load geometry from buffer

	static Geometry* buildPlane(float size);
	static Geometry* buildCube(float size);
	static Geometry* buildSphere(float radius,
		float slices, float stacks);
	~Geometry();
};