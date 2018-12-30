#pragma once
#include "VertexLayout.h"

template<class LayoutType>
class Geometry : public LayoutType {
private:
	GLBuffer<unsigned int> ibo;

public:
	Geometry() : LayoutType() { 
		glBindVertexArray(*this); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); 
		glBindVertexArray(0);
	}
	void loadIndices(std::vector<unsigned int> ib) { ibo.bufferData(ib); }
	size_t elementCount() const { return ibo.size() / sizeof(unsigned int); } // get number of elements
};