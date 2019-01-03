#include <GL/glew.h>
#include <GL/glut.h>

#include "Demo.h"

// Demo base class
Demo::Demo() {}

// Phong shader demo
PhongShaderDemo::PhongShaderDemo() : clicked(false) {
	// renderer
	renderer.setProgram(&phong);

	// geometry
	std::vector<VertexPN> vertices;
	std::vector<unsigned int> indices;
	buildUVSphere(1.0f, 24, 24, vertices, indices);
	sphere.loadData(vertices);
	sphere.loadIndices(indices);

	vertices.clear(); indices.clear();
	buildPlane(4.0f, 4.0f, vertices, indices);
	plane.loadData(vertices);
	plane.loadIndices(indices);

	// camera
	camera.setPosition(glm::vec3(0, 0, 4));
	camera.lookAt(glm::vec3(0, 0, 0));
}

#define MVFLOOR glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)) \
* glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f))

#define MVFRONTWALL glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f)) \
* glm::rotate(glm::mat4(1.0f), 0.0f / 2, glm::vec3(1.0f, 0.0f, 0.0f))

#define MVRIGHTWALL glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f)) \
* glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(0.0f, 1.0f, 0.0f))

#define MVLEFTWALL glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)) \
* glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f))

#define MVBACKWALL glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f)) \
* glm::rotate(glm::mat4(1.0f), PI, glm::vec3(1.0f, 0.0f, 0.0f))

#define MVCEILING glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f)) \
* glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(1.0f, 0.0f, 0.0f))

void PhongShaderDemo::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear framebuffer

	// sphere
	glm::mat4 modelMatrix(1); // model
	glm::mat4 viewMatrix = camera.makeViewMatrix(); // view
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix; // model view
	glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal

	phong.setModelView(modelViewMatrix);
	phong.setProjection(camera.makeProjMatrix());
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 0.5f, 0.0f, 0.5f });
	phong.setAmbient({ 0.05f, 0.05f, 0.05f });
	phong.setLight(glm::vec3(modelViewMatrix * glm::vec4(-1.8, 1.8, 1.8, 1)));
	phong.setLightColor(glm::vec3(1, 1, 1));

	renderer.draw(&sphere); // render

	// floor
	modelMatrix = MVFLOOR; // model
	modelViewMatrix = viewMatrix * modelMatrix; // model view
	normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal
	
	phong.setModelView(viewMatrix * modelMatrix);
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 0.2f, 0.2f, 0.2f });

	renderer.draw(&plane); // render

	// front wall
	modelMatrix = MVFRONTWALL; // model
	modelViewMatrix = viewMatrix * modelMatrix; // model view
	normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal

	phong.setModelView(viewMatrix * modelMatrix);
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 0.2f, 0.2f, 0.2f });

	renderer.draw(&plane); // render

	// right wall
	modelMatrix = MVRIGHTWALL; // model
	modelViewMatrix = viewMatrix * modelMatrix; // model view
	normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal

	phong.setModelView(viewMatrix * modelMatrix);
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 0.1f, 1.0f, 0.1f });

	renderer.draw(&plane); // render

	// left wall
	modelMatrix = MVLEFTWALL; // model
	modelViewMatrix = viewMatrix * modelMatrix; // model view
	normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal

	phong.setModelView(viewMatrix * modelMatrix);
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 1.0f, 0.1f, 0.1f });

	renderer.draw(&plane); // render

	// back wall
	modelMatrix = MVBACKWALL; // model
	modelViewMatrix = viewMatrix * modelMatrix; // model view
	normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal

	phong.setModelView(viewMatrix * modelMatrix);
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 0.2f, 0.2f, 0.2f });

	renderer.draw(&plane); // render

	// ceiling
	modelMatrix = MVCEILING; // model
	modelViewMatrix = viewMatrix * modelMatrix; // model view
	normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelViewMatrix))); // normal

	phong.setModelView(viewMatrix * modelMatrix);
	phong.setNormalMatrix(normalMatrix);
	phong.setAlbedo({ 0.2f, 0.2f, 0.2f });

	renderer.draw(&plane); // render
}

void PhongShaderDemo::reshape(const int w, const int h) {
	glViewport(0, 0, w, h);
	camera.setProjection(PI / 4.0f, w * 1.0f / h, 0.01f, 100.0f);
}

void PhongShaderDemo::mouse(const int button, const int state, const int x, const int y) {
	clicked |= (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
	clicked &= !(button == GLUT_LEFT_BUTTON && state == GLUT_UP);
}

void PhongShaderDemo::motion(const int x, const int y, const int dx, const int dy) {
	const glm::vec3 yaxis(0, 1, 0);
	const glm::vec3 xaxis(1, 0, 0);
	if (clicked) {
		
		camera.rotate(-dx * 5e-2f, glm::vec3(0, 0, 0), yaxis);
		camera.orbit( -dy * 5e-2f, glm::vec3(0, 0, 0), xaxis);
		//camera.rotate(dy * 1e-3f, xaxis);
		//camera.rotate(dx * 1e-3f, yaxis);
		glutPostRedisplay();
	}
}

