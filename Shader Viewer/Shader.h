#pragma once
#include <fstream>
#include <GL\glew.h>
#include <glm/common.hpp>

#include "VertexLayout.h"
#include "NonCopyable.h"

class GLShader : public NonCopyable {
private:
	GLuint handle; // Shader handle
	GLShader(GLenum shaderType);

public:
	void compile(const char* source);
	void compile(std::ifstream& source);
	operator GLuint() const; // cast to GLuint
	~GLShader();

	// shader factory
	static GLShader* VertexShader();
	static GLShader* FragmentShader();
};

// base program class
class GLProgram : public NonCopyable {
private:
	GLuint handle;

protected:
	// helpers for constructing shader
	void link(const GLShader& vshader, const GLShader& fshader);
	GLuint getUniformLocation(const char* unif);

	// helpers for setting uniforms
	template<typename T>
	void setUniform(GLuint unif, T m);

public:
	GLProgram();
	operator GLuint() const; // cast to GLuint
	virtual ~GLProgram();
};



class PhongShader : public GLProgram {
private:
	// Albedo | Ambient Light | Light Direction
	GLuint uAlbedo, uAmbient, uLight;

	// Camera
	GLuint uModelViewMatrix, uProjectionMatrix, uNormalMatrix;

public:
	PhongShader();
	void setAlbedo(const glm::vec3& albedo);
	void setAmbient(const glm::vec3& ambient);
	void setLight(const glm::vec3& light);
	void setModelView(glm::mat4 m);
	void setProjection(glm::mat4 m);
	void setNormalMatrix(glm::mat3 m);
};