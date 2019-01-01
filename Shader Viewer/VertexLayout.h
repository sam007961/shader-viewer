#pragma once
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <assert.h>
#include <cmath>

#include "NonCopyable.h"

// Vertex Types
// Generic Vertex structure
// Contains all possible vertex data
struct Vertex {
	glm::vec3 position; // position
	glm::vec3 normal;   // normal
	glm::vec2 tex;      // uv-coordiantes

	// construct given all data
	Vertex( 
		float x, float y, float z,
		float nx, float ny, float nz,
		float tu, float tv)
		: position(x, y, z), normal(nx, ny, nz), tex(tu, tv) {}
};

/* Vertex subtypes
VertexX {
	...
	static void enableAttributes(unsigned int loc = 0) // setup attribute pointers starting at loc
	VertexX(Vertex v) // must be constructable from generic vertex
}
*/

struct VertexP {
	glm::vec3 position;

	static void enableAttributes(unsigned int loc = 0) {
		glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(loc++);
	}
	VertexP() {}
	VertexP(Vertex v) {
		position = v.position;
	}
};

struct VertexPN {
	glm::vec3 position;
	glm::vec3 normal;

	static void enableAttributes(unsigned int loc = 0) {
		glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE,
			sizeof(VertexPN), (GLvoid*)offsetof(VertexPN, position));
		glEnableVertexAttribArray(loc++);
		glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE,
			sizeof(VertexPN), (GLvoid*)offsetof(VertexPN, normal));
		glEnableVertexAttribArray(loc++);
	}
	VertexPN() {}
	VertexPN(Vertex v) {
		position = v.position;
		normal = v.normal;
	}
};

// Base Buffer Class
template<typename DataType>
class GLBuffer {
private:
	GLuint handle;
	size_t _size;

public:
	GLBuffer() { glGenBuffers(1, &handle); _size = 0; }
	void bufferData(std::vector<DataType> data) { // load data into buffer
		_size = data.size() * sizeof(DataType);
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, _size, &data[0], GL_STATIC_DRAW);
	}
	~GLBuffer() { glDeleteBuffers(1, &handle); }

	size_t size() const { return _size; }
	operator GLuint() const { return handle; } // cast to GLuint
};

// Vertex Buffer Class
template<typename VertexType>
class VertexBuffer : public GLBuffer<VertexType> {
public:
	typedef VertexType Vertex;
	void enableAttributes(unsigned int loc = 0) { // specify location and format
		glBindBuffer(GL_ARRAY_BUFFER, *this);
		VertexType::enableAttributes(loc); 
	}
};

// Base Vertex Layout Class
class VertexLayout : public NonCopyable {
private:
	GLuint handle; // vertex array object handle

public:
	VertexLayout() { glGenVertexArrays(1, &handle); }
	~VertexLayout() { glDeleteVertexArrays(1, &handle); }
	operator GLuint() const { return handle; } // cast to GLuint
};

// InterleavedLayout
// positions and other attributes all interleaved in one buffer
template<typename VertexType>
class InterleavedLayout : public VertexLayout {
private:
	VertexBuffer<VertexType> vbo;

public:
	InterleavedLayout() : VertexLayout() { 
		glBindVertexArray(*this); 
		vbo.enableAttributes(); 
		glBindVertexArray(0);
	}
	void loadData(std::vector<VertexType> vb) { vbo.bufferData(vb); }
};

// VXLayout
// one buffer of VertexP
// another buffer of interleaved attributes X 
// TODO
template<typename X>
class VXLayout : public VertexLayout {
	VertexBuffer<VertexP> pos;
	VertexBuffer<X> attr;

public:
	VXLayout() { /*TODO*/ }
	void loadPositions(std::vector<VertexP> vb) { /*TODO*/ }
	void loadAttributes(std::vector<X> vb) { /*TODO*/ }
};

