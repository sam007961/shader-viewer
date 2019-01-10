#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <GLError.h>

using glm::vec3;

#include "Demos.h"

// globals
#define DEMO PhongTextureShadowDemo
static Demo* g_demo;
static int g_mouseClickX = 0;
static int g_mouseClickY = 0;
static int g_mouseState = 0;
static int g_windowWidth = 640;
static int g_windowHeight = 640;


// state intialization
static void initGlutState();
static void initGLState();

// glut callbacks
static void display();
static void reshape(const int w, const int h);
static void mouse(const int button, const int state, const int x, const int y);
static void motion(const int x, const int y);

// main
int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	initGlutState();
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		throw std::runtime_error("failed to load extentions.");
	initGLState();
	g_demo = new DEMO;
	checkGLErrors();
	glutMainLoop();
	delete g_demo;
	return 0;
}

static void initGlutState() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //  RGBA pixel channels and double buffering
	glutInitWindowSize(512, 512);                              // create a window
	glutCreateWindow("Shader Viewer");                         // title the window
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
}

static void initGLState() {
	// Defualt GL state
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glClearDepth(1.);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glReadBuffer(GL_BACK);
}

static void display() {
	g_demo->draw();
	glutSwapBuffers(); // show the back buffer
}

static void reshape(const int w, const int h) {
	g_windowWidth = w;
	g_windowHeight = h;
	g_demo->reshape(w, h);
	glutPostRedisplay();
}

static void mouse(const int button, const int state, const int x, const int y) {
	g_mouseClickX = x;
	g_mouseClickY = g_windowHeight - y - 1;
	g_mouseState = state;
	g_demo->mouse(button, state, g_mouseClickX, g_mouseClickY);
}

static void motion(const int x, const int y) {
	const int dx = x - g_mouseClickX;
	const int dy = -(g_windowHeight - y - 1 - g_mouseClickY);
	g_mouseClickX = x;
	g_mouseClickY = g_windowHeight - y - 1;
	g_demo->motion(g_mouseClickX, g_mouseClickY, dx, dy);
}