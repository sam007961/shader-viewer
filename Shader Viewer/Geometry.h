#pragma once
#include "VertexLayout.h"

template<class LayoutType>
class Geometry : public LayoutType {
private:
	GLBuffer<unsigned int> ibo;

public:
	void loadIndices(std::vector<unsigned int> ib) { // load indices
		// TODO
	}
	unsigned int elementCount() const { return ibo.size; } // get number of elements
	void bind() { glBindVertexArray(*this); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); }
};