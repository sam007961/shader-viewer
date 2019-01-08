#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"
#include "Light.h"
#include "Framebuffer.h"

class Demo {
public:
	Demo();
	virtual void draw() = 0;
	virtual void reshape(const int w, const int h) = 0;
	virtual void mouse(const int button, const int state, const int x, const int y) = 0;
	virtual void motion(const int x, const int y, const int dx, const int dy) = 0;
};

class RoomDemo : public Demo {
protected:
	typedef Geometry<InterleavedLayout<VertexPNTtb> > Geometry;
	typedef DrawableObject<Geometry> DObject;

	int width, height;
	Geometry geom_sphere, geom_plane;
	Camera camera;
	DObject sphere, floor, ceiling, back_wall, front_wall, left_wall, right_wall;
	PointLight light;

	Renderer renderer;
	LightingShader* shader;

	bool clicked;

	void clear(); // clear frame buffer
	void setProjection(); // set camera projection
	void drawEverything(); // draw entire room

	virtual void draw(const DObject& obj); // draw single object
	
public:
	RoomDemo();
	virtual ~RoomDemo();
	virtual void draw();
	virtual void reshape(const int w, const int h);
	virtual void mouse(const int button, const int state, const int x, const int y);
	virtual void motion(const int x, const int y, const int dx, const int dy);
};

class PhongSolidDemo : public RoomDemo {
public:
	PhongSolidDemo();
};

class PhongTextureDemo : public RoomDemo {
protected:
	typedef GLTexture2D Texture;

	Texture tex_marble, tex_tiles, tex_concrete, tex_mosaic; // diffuse maps
	Texture tex_marble_spec, tex_tiles_spec, tex_concrete_spec, tex_mosaic_spec; // specular maps
	Texture tex_marble_norm, tex_tiles_norm, tex_concrete_norm, tex_mosaic_norm; // normal maps;

public:
	PhongTextureDemo();
};

class DepthShaderDemo : public RoomDemo {
protected:
	typedef GLTexture2D Texture;

	// depth map
	DepthShader depthShader;
	TextureShader textureShader;
	GLFramebuffer depthBuffer;
	Texture depthMap;
	DObject quad;

	virtual void draw(const DObject& obj); // draw single object
	void drawDepth(const DObject& obj);
	void drawDepths();

public:
	DepthShaderDemo();
	virtual void draw();
};

class PhongTextureShadowDemo : public PhongTextureDemo {
protected:
	typedef GLTexture2D Texture;

	// depth map
	DepthShader depthShader;
	GLFramebuffer depthBuffer;
	Texture depthMap;
	void drawShadow(const DObject& obj);
	void drawShadows();

	virtual void draw(const DObject& obj); // draw single object

public:
	PhongTextureShadowDemo();
	virtual void draw();
};