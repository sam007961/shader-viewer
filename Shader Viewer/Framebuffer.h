#pragma once
#include "GLObject.h"

class GLFramebuffer : public GLObject {
public:
	GLFramebuffer();
	void clear();
	~GLFramebuffer();
};