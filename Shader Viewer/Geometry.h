#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Shader.h"

// Functions and consts for vertex and index buffer lengths 
static const int VBLEN_PLANE = 4;
static const int VBLEN_CUBE = 24;
inline int VBLEN_SPHERE(int slices, int stacks) {
	return (slices + 1) * (stacks + 1);
}

static const int IBLEN_PLANE = 6;
static const int IBLEN_CUBE = 36;
inline int IBLEN_SPHERE(int slices, int stacks) {
	return slices * stacks * 6;
}

static const double PI = glm::pi<double>();
static const double EPS = glm::epsilon<double>();
static const double EPS2 = EPS * EPS;
static const double EPS3 = EPS2 * EPS;

// Vertex structure
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
class Geometry {
protected:
	GLuint vbo, ibo;                      // vertex and index buffer object handles
	int vboLen, iboLen;                   // length of buffers

	void copyBuffers(const Vertex*,
		unsigned short const*, int, int);
public:
	Geometry();                           // generate vbo and ibo
	Geometry(const Geometry&);            // copy geometry
	Geometry(const Vertex*, 
		unsigned short const*, int, int); // load geometry from buffer

	void draw(const GLProgram&) const;             // draw geometry using the specified shader

	~Geometry();

};

// Plane class
class Plane : public Geometry{
public:
	Plane();
	Plane(const float&);
};