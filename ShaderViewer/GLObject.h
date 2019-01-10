#pragma once
#include <GL\glew.h>
class GLObject {
protected:
	GLuint handle; // object handle
	GLObject() {}
	GLObject(GLuint handle) : handle(handle) {}

private:
	// Non-copyable
	GLObject(const GLObject& other) = delete;
	GLObject& operator=(const GLObject& other) = delete;

public:

	operator GLuint() const { return handle; }
	virtual ~GLObject() {}
};