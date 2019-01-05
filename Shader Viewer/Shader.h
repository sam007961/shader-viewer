#pragma once
#include <fstream>
#include <GL\glew.h>
#include <glm/common.hpp>

#include "VertexLayout.h"
#include "GLObject.h"
#include "Material.h"
#include "Texture.h"

class GLShader : public GLObject {
private:
	GLShader(GLenum shaderType);

public:
	void compile(const char* source);
	void compile(std::ifstream& source);
	virtual ~GLShader();

	// shader factory
	static GLShader* VertexShader();
	static GLShader* FragmentShader();
};

// base program class
class GLProgram : public GLObject {
protected:
	// helpers for constructing shader
	void link(const GLShader& vshader, const GLShader& fshader);
	GLuint getUniformLocation(const char* unif);

	// helpers for setting uniforms
	template<typename T>
	void setUniform(GLuint unif, T m);

public:
	GLProgram();
	virtual ~GLProgram();
};

class LightingShader : public GLProgram {
private:
	// Ambient Light | Light Direction | Light Color
	GLuint uAmbient, uLight, uLightColor;

	// Camera
	GLuint uModelViewMatrix, uProjectionMatrix, uNormalMatrix;

public:
	LightingShader(const char* frag_file);
	void setAmbient(const glm::vec3& ambient); // set ambient light
	void setLight(const glm::vec3& light, glm::mat4 view=glm::mat4(1)); // set light position
	void setLightColor(const glm::vec3& lightColor); // set light color

	void setModelView(glm::mat4 m); // set modelViewMatrix and automatically set normalMatrix
	void setProjection(glm::mat4 m); // set projectionMatrix
	virtual void loadMaterial(const Material& material); // load uniforms from material
};

class PhongSolid : public LightingShader {
private:
	// Color
	GLuint uColor;

public:
	PhongSolid();
	void setColor(const glm::vec3& color);
	virtual void loadMaterial(const Material& material);
};

class PhongTexture : public LightingShader {
private:
	GLuint uTexture;

public:
	PhongTexture();
	void setTexture(GLuint texture);
	virtual void loadMaterial(const Material& material);
};