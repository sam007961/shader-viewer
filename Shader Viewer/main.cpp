#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include "Geometry.h"
#include "Shader.h"
#include "Renderer.h"
#include <string>

Renderer g_renderer;
Geometry<InterleavedLayout<VertexPN> >* g_target;
PhongShader* g_phong;

void checkGlErrors() {
	const GLenum errCode = glGetError();

	if (errCode != GL_NO_ERROR) {
		std::string error("GL Error: ");
		error += reinterpret_cast<const char*>(gluErrorString(errCode));
		std::cerr << error << std::endl;
		throw std::runtime_error(error);
	}
}

static void initShaders() {
	g_phong = new PhongShader();
	g_target = new Geometry<InterleavedLayout<VertexPN> >();
	g_renderer.setProgram(g_phong);

	std::vector<VertexPN> vertices;
	VertexPN vert;
	vert.position = glm::vec3(-1, 1, 0);
	vert.normal = glm::vec3(0, 0, 1);
	vertices.push_back(vert);

	vert.position = glm::vec3(-1, -1, 0);
	vert.normal = glm::vec3(0, 0, 1);
	vertices.push_back(vert);

	vert.position = glm::vec3(1, 1, 0);
	vert.normal = glm::vec3(0, 0, 1);
	vertices.push_back(vert);

	vert.position = glm::vec3(1, -1, 0);
	vert.normal = glm::vec3(0, 0, 1);
	vertices.push_back(vert);

	g_target->loadData(vertices);

	std::vector<unsigned int> indices = { 0, 1, 2, 2, 1, 3 };
	g_target->loadIndices(indices);
	g_phong->setModelView(glm::mat4(1));
	g_phong->setProjection(glm::mat4(1));
	g_phong->setAlbedo({ 0.5, 0.7, 0.0 });
	g_phong->setAmbient({ 0, 0, 0 });
	g_phong->setLight({ -1, -1, -1 });

	checkGlErrors();
}

static void draw() {
	g_renderer.draw(g_target);
}

static void display() {
	//glUseProgram(*basicShader);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                   // clear framebuffer color&depth
	draw();
	glutSwapBuffers();                                    // show the back buffer (where we rendered stuff)
}

void glutTimer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, glutTimer, 1);
}

int main(int argc, char * argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //  RGBA pixel channels and double buffering
	glutInitWindowSize(512, 512);                              // create a window
	glutCreateWindow("Shader Viewer");                           // title the window
	glutDisplayFunc(display);
	glutTimerFunc(10, glutTimer, 1);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		throw std::runtime_error("failed to load extentions.");
	}

	glClearColor(0, 0, 0, 1.);
	glClearDepth(0.);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);
	glReadBuffer(GL_BACK);

	initShaders();
	
	glutTimerFunc(10, glutTimer, 1);
	glutMainLoop();
	
	//Plane plane(1.0f);
	return 0;
}