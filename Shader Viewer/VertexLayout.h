#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "NonCopyable.h"
#include "Geometry.h"

// vertex types
struct VertexP {
	glm::vec3 position;
	static void EnableAttributes();

	VertexP(Vertex v);
};

struct VertexPN {
	glm::vec3 position;
	glm::vec3 normal;
	static void EnableAttributes();

	VertexPN(Vertex v);
};

template<typename VertexT>
class VertexBuffer {
private:
	GLuint handle;
	size_t size;

public:
	VertexBuffer() : handle(glGenBuffers(1, &handle)) {};
	void bufferData(const std::vector<VertexT>& data) {
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(VertexT), &data[0], GL_STATIC_DRAW);
	}
	void enable() { VertexT::EnableAttributes(); }
	operator GLuint() const { return handle }; // cast to GLuint
};

// vertex layout class
class VertexLayout : public NonCopyable {
private:
	GLuint handle; // vertex array object handle

protected:
	VertexLayout();

public:
	virtual unsigned int elementCount() const = 0; // get number of elements
	virtual void loadGeometry(const Geometry& geometry) = 0; // load data from geometry
	operator GLuint() const; // cast to GLuint
	~VertexLayout();
};

// vertex layouts
// V = position
// N = normal
// T = texture coordinates
// C = color
// t = tangent
// c = cotangent

template<typename VertexT>
class InterleavedLayout : public VertexLayout {
	VertexBuffer<VertexT> vbo;



};
class VLayout : public VertexLayout {
private:

public:
	VLayout();
	virtual void loadGeometry(const Geometry& geometry);
};

class VNLayout : public VertexLayout {
public:
	VNLayout();
	virtual void loadGeometry(const Geometry& geometry);
};
