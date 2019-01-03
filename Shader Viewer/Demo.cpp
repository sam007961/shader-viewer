#include "Demo.h"
// Demo base class
Demo::Demo() {}

// Phong shader demo
PhongShaderDemo::PhongShaderDemo() {
	// renderer
	renderer.setProgram(&phong);

	// geometry
	std::vector<VertexPN> vertices;
	std::vector<unsigned int> indices;
	buildUVSphere(1.0, 24, 24, vertices, indices);
	target.loadData(vertices);
	target.loadIndices(indices);

	// camera
	camera.setPosition(glm::vec3(0, 1, 4));
	camera.lookAt(glm::vec3(0, 0, 0));

	// shader
	updateCameraUniforms();
	phong.setAlbedo({ 0.5f, 0.0f, 0.5f });
	phong.setAmbient({ 0.1f, 0.1f, 0.1f });
	phong.setLight({ -1.0f, 3.0f, 0.0f });
}

void PhongShaderDemo::updateCameraUniforms() {
	phong.setModelView(camera.makeViewMatrix());
	phong.setProjection(camera.makeProjMatrix());
}

void PhongShaderDemo::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear framebuffer
	updateCameraUniforms();
	renderer.draw(&target);
}

void PhongShaderDemo::reshape(const int w, const int h) {
	glViewport(0, 0, w, h);
	camera.setProjection(PI / 4.0f, w * 1.0f / h, 0.01f, 100.0f);
}

void PhongShaderDemo::mouse(const int button, const int state, const int x, const int y) {
	
}

void PhongShaderDemo::motion(const int x, const int y, const int state, const int dx, const int dy) {

}

