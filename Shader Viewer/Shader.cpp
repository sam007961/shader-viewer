#include "Shader.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// GLSHADER ///////////////////////////////////////////////////////////////////////////////////
GLShader::GLShader(GLenum shaderType) : handle(glCreateShader(shaderType)) {};

GLShader::operator GLuint() const {
	return handle;
}

GLShader::~GLShader() {
	glDeleteShader(handle);
}

void GLShader::compile(const char* source) {
	GLint compiled = 0;  // Compiled flag
	const char *ptrs[] = { source };
	const GLint lens[] = { std::strlen(source) };
	glShaderSource(handle, 1, ptrs, lens);
	glCompileShader(handle);
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint logSize = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> errorLog(logSize);
		glGetShaderInfoLog(handle, logSize, &logSize, &errorLog[0]);
		std::cerr << &errorLog[0] << std::endl;
		throw std::runtime_error("Failed to compile shader.");
	}
}

void GLShader::compile(std::ifstream& source) {
	std::vector<char> text;
	source.seekg(0, std::ios_base::end);
	std::streampos fileSize = source.tellg();
	text.resize(fileSize);

	source.seekg(0, std::ios_base::beg);
	source.read(&text[0], fileSize);
	compile(&text[0]);
}

GLShader& GLShader::VertexShader() { return GLShader(GL_VERTEX_SHADER); }
GLShader& GLShader::FragmentShader() { return GLShader(GL_FRAGMENT_SHADER); }

// GLPROGRAM //////////////////////////////////////////////////////////////////////////////////
GLProgram::GLProgram() : handle(glCreateProgram()) {}

void GLProgram::link(const GLShader& vshader, const GLShader& fshader) {
	GLint linked = 0; // Linked flag
	glAttachShader(handle, vshader);
	glAttachShader(handle, fshader);
	glLinkProgram(handle);
	glDetachShader(handle, vshader);
	glDetachShader(handle, fshader);
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);
	if (!linked)
		throw std::runtime_error("Failed to link shaders.");

	// get camera uniforms
	uModelViewMatrix = getUniformLocation("uModelViewMatrix");
	uProjectionMatrix = getUniformLocation("uProjectionMatrix");
}

GLuint GLProgram::getUniformLocation(const char* unif) {
	return glGetUniformLocation(handle, unif);
}

void GLProgram::setUniform(GLuint unif, glm::mat4 m) {
	glUseProgram(handle);
	glUniformMatrix4fv(unif,
		1, GL_FALSE, glm::value_ptr(m[0]));
	glUseProgram(0);
}


void GLProgram::setModelView(glm::mat4 m) {
	setUniform(uModelViewMatrix, m);
}

void GLProgram::setProjection(glm::mat4 m) {
	setUniform(uProjectionMatrix, m);
}

GLProgram::operator GLuint() const { return handle; }

GLProgram::~GLProgram() { glDeleteProgram(handle); }

// SHADER PROGRAMS ////////////////////////////////////////////////////////////////////////////
PhongShader::PhongShader() : GLProgram() {
	// get uniforms
	uAlbedo = glGetUniformLocation(*this, "uAlbedo");
	uAmbient = glGetUniformLocation(*this, "uAmbient");
	uLight = glGetUniformLocation(*this, "uLight");
}

void PhongShader::setAlbedo(const glm::vec3& albedo) {
	assert(uAlbedo >= 0);

	glUseProgram(*this);
	glUniform3f(uAlbedo, albedo[0], albedo[1], albedo[2]);
	glUseProgram(0);
}
void PhongShader::setAmbient(const glm::vec3& ambient) {
	assert(uAmbient >= 0);

	glUseProgram(*this);
	glUniform3f(uAmbient, ambient[0], ambient[1], ambient[2]);
	glUseProgram(0);
}
void PhongShader::setLight(const glm::vec3& light) {
	assert(uLight >= 0);

	glUseProgram(*this);
	glUniform3f(uLight, light[0], light[1], light[2]);
	glUseProgram(0);
}


PickShader::PickShader() : GLProgram() {
	uTessFact = glGetUniformLocation(*this, "uTessFact");
}


void PickShader::setTessFact(unsigned int n) {
	assert(uTessFact >= 0);
	glUseProgram(*this);
	glUniform1i(uTessFact, n);
	glUseProgram(0);
}