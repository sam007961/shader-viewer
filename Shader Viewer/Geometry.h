#pragma once
#include <cmath>

#include "VertexLayout.h"
#include "Constants.h"

// Geometry class
template<class LayoutType>
class Geometry : public LayoutType {
private:
	GLBuffer<unsigned int> ibo;
	unsigned int n_elements;

public:
	Geometry() : LayoutType() { 
		glBindVertexArray(*this); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); 
		glBindVertexArray(0);
	}
	void loadIndices(std::vector<unsigned int> ib) { 
		ibo.bufferData(ib); 
		n_elements = (unsigned int) ibo.size() / sizeof(unsigned int); 
	}
	inline unsigned int elementCount() const { return n_elements; } // get number of elements
};

// function to construct sphere geometry
template<typename VertexType>
void buildUVSphere(const float radius, const unsigned int slices, const unsigned int stacks,
	std::vector<VertexType>& vertices, std::vector<unsigned int>& indices) {
	// allocate storage
	vertices.resize((slices + 1) * (stacks + 1));
	indices.resize(slices * stacks * 6);
	auto vert = vertices.begin();
	auto indx = indices.begin();

	// calculate sines and cosines
	const float sliceRad = 2.0f * PI / slices;
	const float stackRad = PI / stacks;

	// populate vertices
	for (unsigned int u = 0; u < slices + 1; u++) {
		for (unsigned int v = 0; v < stacks + 1; v++) {
			float x, y, z;
			x = cos(sliceRad * u) * sin(stackRad * v);
			y = sin(sliceRad * u) * sin(stackRad * v);
			z = cos(stackRad * v);
			*vert++ = Vertex(
				x * radius, y * radius, z * radius,
				x, y, z,
				1.0f / slices * u, 1.0f / stacks * v
			);
		}
	}

	// populate indices
	for (unsigned int u = 0; u < slices; u++) {
		for (unsigned int v = 0; v < stacks; v++) {
			*indx++ = (stacks + 1) * u + v;
			*indx++ = (stacks + 1) * (u + 1) + v + 1;
			*indx++ = (stacks + 1) * u + v + 1;

			*indx++ = (stacks + 1) * u + v;
			*indx++ = (stacks + 1) * (u + 1) + v;
			*indx++ = (stacks + 1) * (u + 1) + v + 1;
		}
	}
}


