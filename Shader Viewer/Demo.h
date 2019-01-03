#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"

class Demo {
public:
	Demo();
	virtual void draw() = 0;
	virtual void reshape(const int w, const int h) = 0;
	virtual void mouse(const int button, const int state, const int x, const int y) = 0;
	virtual void motion(const int x, const int y, const int state, const int dx, const int dy) = 0;
};

//g_mouseLClickButton |= (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
//g_mouseRClickButton |= (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN);
//g_mouseMClickButton |= (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN);
//
//g_mouseLClickButton &= !(button == GLUT_LEFT_BUTTON && state == GLUT_UP);
//g_mouseRClickButton &= !(button == GLUT_RIGHT_BUTTON && state == GLUT_UP);
//g_mouseMClickButton &= !(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP);
//
//g_mouseClickDown = g_mouseLClickButton || g_mouseRClickButton || g_mouseMClickButton;

class PhongShaderDemo: public Demo {
private:
	Renderer renderer;
	Camera camera;
	Geometry<InterleavedLayout<VertexPN> > target;
	PhongShader phong;

	void updateCameraUniforms();

public:
	PhongShaderDemo();
	virtual void draw();
	virtual void reshape(const int w, const int h);
	virtual void mouse(const int button, const int state, const int x, const int y);
	virtual void motion(const int x, const int y, const int state, const int dx, const int dy);

};