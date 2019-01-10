#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"
#include "Light.h"
#include "Framebuffer.h"

class Demo {
public:
	Demo() {};
	virtual void draw() = 0;
	virtual void reshape(const int w, const int h) = 0;
	virtual void mouse(const int button, const int state, const int x, const int y) = 0;
	virtual void motion(const int x, const int y, const int dx, const int dy) = 0;
};