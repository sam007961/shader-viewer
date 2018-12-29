#pragma once
#include <fstream>
#include <GL\glew.h>
#include <glm/common.hpp>

#include "Geometry.h"
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
	static GLShader& VertexShader();
	static GLShader& FragmentShader();
};

// base program class
class GLProgram : public NonCopyable {
private:
	GLuint handle;
	GLuint uModelViewMatrix, uProjectionMatrix;

protected:
	GLuint getUniformLocation(const char* unif);
	void setUniform(GLuint unif, glm::mat4 m);

public:
	GLProgram();
	virtual void link(const GLShader& vshader, const GLShader& fshader);
	void setModelView(glm::mat4 m);
	void setProjection(glm::mat4 m);
	operator GLuint() const; // cast to GLuint
	virtual ~GLProgram();

	// vertex layout factory
	virtual VertexLayout& createLayout() const = 0;

};



class PhongShader : public GLProgram {
private:
	// Albedo | Ambient Light | Light Direction
	GLuint uAlbedo, uAmbient, uLight;

public:
	PhongShader();
	void setAlbedo(const glm::vec3& albedo);
	void setAmbient(const glm::vec3& ambient);
	void setLight(const glm::vec3& light);
};


class PickShader : public GLProgram {
private:
	GLuint uTessFact;

public:
	PickShader();
	void setTessFact(unsigned int n);
};