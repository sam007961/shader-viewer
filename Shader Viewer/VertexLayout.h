#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "NonCopyable.h"

// Vertex Types
// Generic Vertex structure
struct Vertex {
	glm::vec3 position; // position
	glm::vec3 normal;   // normal
	glm::vec2 tex;      // uv-coordiantes

	Vertex(
		float x, float y, float z,
		float nx, float ny, float nz,
		float tu, float tv);
};

/* Vertex subtypes
VertexX {
	...
	static void enableAttributes(unsigned int i = 0) // setup attribute pointers
	VertexX(Vertex v) // must be constructable from generic vertex
}
*/

struct VertexP {
	glm::vec3 position;

	static void enableAttributes(unsigned int i = 0);
	VertexP(Vertex v);
};

struct VertexPN {
	glm::vec3 position;
	glm::vec3 normal;

	static void enableAttributes(unsigned int i = 0);
	VertexPN(Vertex v);
};

// Base Buffer Class
template<typename DataType>
class GLBuffer {
private:
	GLuint handle;
	size_t _size;

public:
	GLBuffer() : handle(glGenBuffers(1, &handle)) {};
	void bufferData(std::vector<VertexT> data) { // load data into buffer
		_size = data.size() * sizeof(VertexT);
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, _size, &data[0], GL_STATIC_DRAW);
	}
	~GLBuffer() { glDeleteBuffers(1, &handle); }

	size_t size() { return _size; }
	operator GLuint() const { return handle }; // cast to GLuint
};

// Vertex Buffer Class
template<typename VertexType>
class VertexBuffer : public GLBuffer<VertexType> {
public:
	typedef VertexType Vertex;
	void enableAttributes(unsigned int i = 0) { // specify location and format
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		VertexType::enableAttributes(i); 
	}
};

// Base Vertex Layout Class
class VertexLayout : public NonCopyable {
private:
	GLuint handle; // vertex array object handle

protected:
	VertexLayout();

public:
	virtual void loadData(std::vector<Vertex> vb) = 0; // load data from array of Vertex
	operator GLuint() const; // cast to GLuint
	~VertexLayout();
};

// InterleavedLayout
// positions and other attributes all interleaved in one buffer
template<typename VertexT>
class InterleavedLayout : public VertexLayout {
private:
	VertexBuffer<VertexT> vbo;

public:
	virtual void loadData(std::vector<Vertex> vb);
};

// VXLayout
// one buffer of VertexP
// another buffer of interleaved attributes X 
template<typename X>
class VXLayout : public VertexLayout {
	VertexBuffer<VertexP> pos;
	VertexBuffer<X> attr;

public:
	virtual void loadData(std::vector<Vertex> vb);
};

