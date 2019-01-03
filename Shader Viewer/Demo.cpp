#include <GL/glew.h>
#include <GL/glut.h>

#include "Demo.h"

// Demo base class
Demo::Demo() {}

// Room demo class
RoomDemo::RoomDemo() : clicked(false) {
	// geometry
	std::vector<VertexPN> vertices;
	std::vector<unsigned int> indices;
	buildUVSphere(1.0f, 24, 24, vertices, indices);
	geom_sphere.loadData(vertices);
	geom_sphere.loadIndices(indices);

	vertices.clear(); indices.clear();
	buildPlane(4.0f, 4.0f, vertices, indices);
	geom_plane.loadData(vertices);
	geom_plane.loadIndices(indices);

	// materials
	Material grey = { { 0.2f, 0.2f, 0.2f },{ 0.025f, 0.025f, 0.025f } };
	Material purple = { { 0.5f, 0.0f, 0.5f },{ 0.025f, 0.025f, 0.025f } };
	Material red = { { 1.0f, 0.1f, 0.1f },{ 0.025f, 0.025f, 0.025f } };
	Material green = { { 0.1f, 1.0f, 0.1f },{ 0.025f, 0.025f, 0.025f } };

	// drawables
	sphere.setGeometry(&geom_sphere);
	floor.setGeometry(&geom_plane);
	ceiling.setGeometry(&geom_plane);
	back_wall.setGeometry(&geom_plane);
	front_wall.setGeometry(&geom_plane);
	left_wall.setGeometry(&geom_plane);
	right_wall.setGeometry(&geom_plane);

	sphere.setMaterial(purple);
	floor.setMaterial(grey);
	ceiling.setMaterial(grey);
	back_wall.setMaterial(grey);
	front_wall.setMaterial(grey);
	left_wall.setMaterial(red);
	right_wall.setMaterial(green);

	sphere.setPosition({ 0, 0, 0 });
	floor.setPosition({ 0, -2, 0 });
	ceiling.setPosition({ 0, 2, 0 });
	back_wall.setPosition({ 0, 0, 2 });
	front_wall.setPosition({ 0, 0, -2 });
	left_wall.setPosition({ -2, 0, 0 });
	right_wall.setPosition({ 2, 0, 0 });

	floor.rotate(-PI / 2, XAXIS);
	ceiling.rotate(PI / 2, XAXIS);
	back_wall.rotate(PI, XAXIS);
	left_wall.rotate(PI / 2, YAXIS);
	right_wall.rotate(-PI / 2, YAXIS);

	// camera
	camera.setPosition(glm::vec3(0, 0, 4));
	camera.lookAt(glm::vec3(0, 0, 0));
}

RoomDemo::~RoomDemo() { delete shader; }

void RoomDemo::draw(const DObject& obj, glm::mat4 viewMatrix) {
	renderer.setProgram(shader);
	glm::mat4 modelViewMatrix = viewMatrix * obj.makeModelMatrix(); // model view
	shader->setModelView(modelViewMatrix);
	shader->loadMaterial(obj.getMaterial());
	renderer.draw(obj.getGeometry()); // render
}

void RoomDemo::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear framebuffer

	glm::mat4 viewMatrix = camera.makeViewMatrix(); // view
	glm::mat4 projectionMatrix = camera.makeProjMatrix();
	shader->setProjection(projectionMatrix);

	draw(sphere, viewMatrix);
	draw(floor, viewMatrix);
	draw(ceiling, viewMatrix);
	draw(back_wall, viewMatrix);
	draw(front_wall, viewMatrix);
	draw(left_wall, viewMatrix);
	draw(right_wall, viewMatrix);
}

void RoomDemo::reshape(const int w, const int h) {
	glViewport(0, 0, w, h);
	camera.setProjection(PI / 4.0f, w * 1.0f / h, 0.01f, 100.0f);
}

void RoomDemo::mouse(const int button, const int state, const int x, const int y) {
	clicked |= (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
	clicked &= !(button == GLUT_LEFT_BUTTON && state == GLUT_UP);
}

void RoomDemo::motion(const int x, const int y, const int dx, const int dy) {
	const glm::vec3 yaxis(0, 1, 0);
	const glm::vec3 xaxis(1, 0, 0);
	if (clicked) {

		camera.rotate(-dx * 5e-2f, glm::vec3(0, 0, 0), yaxis);
		camera.orbit(-dy * 5e-2f, glm::vec3(0, 0, 0), xaxis);
		glutPostRedisplay();
	}
}

// Phong shader demo
PhongSolidDemo::PhongSolidDemo() : RoomDemo() {
	// shader
	shader = new PhongSolid();
}



void PhongSolidDemo::draw() {
	
	shader->setLight(glm::vec3(-1.8, 1.8, 1.8), camera.makeViewMatrix());
	shader->setLightColor(glm::vec3(1, 1, 1));
	RoomDemo::draw();
}



