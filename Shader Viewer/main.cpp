#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using glm::vec3;

#include "Geometry.h"
#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"

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
	std::vector<unsigned int> indices;
	buildUVSphere(1.0, 24, 24, vertices, indices);
	g_target->loadData(vertices);
	g_target->loadIndices(indices);
	Camera camera;
	camera.setPosition(vec3(0, 1, 2));
	camera.lookAt(vec3(0, 0, 0));
	camera.setProjection(PI / 2.0f, 1.0f, 0.01f, 100.0f);
	auto m = camera.makeViewMatrix();
	for (int i = 0; i < 16; i++) {
		std::cout << glm::value_ptr(m[0])[i] << std::endl;
	}

	g_phong->setModelView(camera.makeViewMatrix());
	g_phong->setProjection(camera.makeProjMatrix());
	g_phong->setAlbedo({ 0.5, 0.0, 0.5 });
	g_phong->setAmbient({ 0, 0, 0 });
	g_phong->setLight({ -1, 3, 0 });

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

static void reshape(const int w, const int h) {
	glViewport(0, 0, w, h);
	glutPostRedisplay();
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
	glutReshapeFunc(reshape);
	glutTimerFunc(10, glutTimer, 1);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		throw std::runtime_error("failed to load extentions.");
	}

	glClearColor(0, 0, 0, 1.);
	glClearDepth(1.);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glReadBuffer(GL_BACK);

	initShaders();
	
	glutTimerFunc(10, glutTimer, 1);
	glutMainLoop();
	
	//Plane plane(1.0f);
	return 0;
}