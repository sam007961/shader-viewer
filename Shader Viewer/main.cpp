#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include "Geometry.h"
#include "Shader.h"


std::shared_ptr<Shader> basicVS;
std::shared_ptr<Shader> basicFS;
std::shared_ptr<GLProgram> basicShader;


static void initShaders() {
	std::ifstream fVShader("Shaders/basic.vshader");
	if (!fVShader) {
		std::runtime_error("Could not open vertex shader");
	}
	basicVS.reset(new Shader(GL_VERTEX_SHADER, fVShader));
	std::ifstream fFShader("Shaders/solid.fshader");
	basicFS.reset(new Shader(GL_FRAGMENT_SHADER, fFShader));
	basicShader.reset(new GLProgram(*basicVS, *basicFS));

	GLINPUT(*basicShader,
		ATTR(aPosition)
		ATTR(aNormal)
		UNIF(uColor)
	);
}

static void draw() {
	static const Plane plane(2.0f);
	glUseProgram(*basicShader);
	
	glUniform3f(basicShader->unif["uColor"], 1.0f, 0.0f, 0.0f);
	plane.draw(*basicShader);
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
	/*VertexPN vbx[VBLEN_CUBE];
	unsigned short idx[IBLEN_CUBE];*/
	//makeCube(1, vbx, idx);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //  RGBA pixel channels and double buffering
	glutInitWindowSize(512, 512);                              // create a window
	glutCreateWindow("White Noise");                           // title the window
	glutDisplayFunc(display);
	glutTimerFunc(10, glutTimer, 1);
	glewInit();

	glClearColor(.2, .2, .2, 1.);
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