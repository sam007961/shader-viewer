#include <GL/glew.h>
#include <GL/glut.h>

#include "Demo.h"

// Demo base class
Demo::Demo() {}

// Room demo class
RoomDemo::RoomDemo() : clicked(false) {
	// geometry
	std::vector<VertexPNTtb> vertices;
	std::vector<unsigned int> indices;
	buildUVSphere(1.0f, 24, 24, vertices, indices);
	geom_sphere.loadData(vertices);
	geom_sphere.loadIndices(indices);

	vertices.clear(); indices.clear();
	buildPlane(4.0f, 4.0f, vertices, indices);
	geom_plane.loadData(vertices);
	geom_plane.loadIndices(indices);

	// materials
	Material grey = { { 0.2f, 0.2f, 0.2f }, { 0.05f, 0.05f, 0.05f } };
	Material purple = { { 0.5f, 0.0f, 0.5f }, { 0.05f, 0.05f, 0.05f } };
	Material red = { { 1.0f, 0.1f, 0.1f }, { 0.05f, 0.05f, 0.05f } };
	Material green = { { 0.1f, 1.0f, 0.1f }, { 0.05f, 0.05f, 0.05f } };

	// light
	light = Light(-1.8, 1.8, 1.5);

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

void RoomDemo::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void RoomDemo::setProjection() {
	glm::mat4 projectionMatrix = camera.makeProjMatrix();
	shader->setProjection(projectionMatrix);
}

void RoomDemo::draw(const DObject& obj) {
	renderer.setProgram(shader);
	glm::mat4 viewMatrix = camera.makeViewMatrix(); // view
	glm::mat4 modelViewMatrix = viewMatrix * obj.makeModelMatrix(); // model view
	shader->setLight(light, viewMatrix);
	shader->setModelView(modelViewMatrix);
	shader->loadMaterial(obj.material());
	renderer.draw(obj.geometry()); // render
}

void RoomDemo::drawEverything() {
	draw(sphere);
	draw(floor);
	draw(ceiling);
	draw(back_wall);
	draw(front_wall);
	draw(left_wall);
	draw(right_wall);
}

void RoomDemo::draw() {
	clear();
	setProjection();
	drawEverything();
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

// Solid Phong shader demo
PhongSolidDemo::PhongSolidDemo() : RoomDemo() {
	// shader
	shader = new PhongSolid();
	shader->setLightColor(glm::vec3(1, 1, 1));
}


// Texuture Phong shader demo
PhongTextureDemo::PhongTextureDemo() : RoomDemo() {
	// shader
	shader = new PhongTexture();
	shader->setLightColor(glm::vec3(1, 1, 1));
	
	// textures
	// diffuse maps
	tex_marble.loadData("./Textures/marble.png");
	tex_tiles.loadData("./Textures/tiles.jpg");
	tex_concrete.loadData("./Textures/concrete.png");
	tex_mosaic.loadData("./Textures/mosaic.jpg");
	
	// spculular maps
	tex_marble_spec.loadData("./Textures/marble_SPEC.tga");
	tex_tiles_spec.loadData("./Textures/tiles_SPEC.tga");
	tex_concrete_spec.loadData("./Textures/concrete_SPEC.tga");
	tex_mosaic_spec.loadData("./Textures/mosaic_SPEC.tga");

	// normal maps
	tex_marble_norm.loadData("./Textures/marble_NORM.png");
	tex_tiles_norm.loadData("./Textures/tiles_NORM.png");
	tex_concrete_norm.loadData("./Textures/concrete_NORM.png");
	tex_mosaic_norm.loadData("./Textures/mosaic_NORM.png");



	// materials
	Material marble, tiles, concrete, mosaic;

	marble.ambient = { 0.05, 0.05, 0.05 };
	marble.textures[0] = tex_marble;
	marble.textures[1] = tex_marble_spec;
	marble.textures[2] = tex_marble_norm;

	tiles.ambient = { 0.05, 0.05, 0.05 };
	tiles.textures[0] = tex_tiles;
	tiles.textures[1] = tex_tiles_spec;
	tiles.textures[2] = tex_tiles_norm;

	concrete.ambient = { 0.05, 0.05, 0.05 };
	concrete.textures[0] = tex_concrete;
	concrete.textures[1] = tex_concrete_spec;
	concrete.textures[2] = tex_concrete_norm;

	mosaic.ambient = { 0.05, 0.05, 0.05 };
	mosaic.textures[0] = tex_mosaic;
	mosaic.textures[1] = tex_mosaic_spec;
	mosaic.textures[2] = tex_mosaic_norm;

	sphere.setMaterial(marble);
	floor.setMaterial(tiles);
	ceiling.setMaterial(concrete);
	back_wall.setMaterial(mosaic);
	front_wall.setMaterial(mosaic);
	left_wall.setMaterial(mosaic);
	right_wall.setMaterial(mosaic);
}
