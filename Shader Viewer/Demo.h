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
	virtual void motion(const int x, const int y, const int dx, const int dy) = 0;
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

class RoomDemo : public Demo {
protected:
	typedef Geometry<InterleavedLayout<VertexPNT> > Geometry;
	typedef DrawableObject<Geometry> DObject;

	Geometry geom_sphere, geom_plane;
	Camera camera;
	DObject sphere, floor, ceiling, back_wall, front_wall, left_wall, right_wall;

	Renderer renderer;
	LightingShader* shader;

	bool clicked;

	void draw(const DObject& obj, glm::mat4 viewMatrix);
	
public:
	RoomDemo();
	~RoomDemo();
	virtual void draw();
	virtual void reshape(const int w, const int h);
	virtual void mouse(const int button, const int state, const int x, const int y);
	virtual void motion(const int x, const int y, const int dx, const int dy);
};

class PhongSolidDemo : public RoomDemo {
public:
	PhongSolidDemo();
	virtual void draw();
};

//class PhongShaderDemo : public Demo {
//private:
//	Renderer renderer;
//	Camera camera;
//	Geometry<InterleavedLayout<VertexPN> > sphere, plane;
//	PhongShader phong;
//	bool clicked;
//
//public:
//	PhongShaderDemo();
//	virtual void draw();
//	virtual void reshape(const int w, const int h);
//	virtual void mouse(const int button, const int state, const int x, const int y);
//	virtual void motion(const int x, const int y, const int dx, const int dy);
//
//};