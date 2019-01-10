#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
#include "Constants.h"
// GLSHADER ///////////////////////////////////////////////////////////////////////////////////
GLShader::GLShader(GLenum shaderType) : GLObject(glCreateShader(shaderType)) {};


GLShader::~GLShader() {
	glDeleteShader(handle);
}

void GLShader::compile(const char* source) {
	GLint compiled = 0;  // Compiled flag
	const char *ptrs[] = { source };
	const GLint lens[] = { (GLint)std::strlen(source) };
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

Shader GLShader::VertexShader()   { return std::shared_ptr<GLShader>(new GLShader(GL_VERTEX_SHADER));   }
Shader GLShader::FragmentShader() { return std::shared_ptr<GLShader>(new GLShader(GL_FRAGMENT_SHADER)); }

// GLPROGRAM //////////////////////////////////////////////////////////////////////////////////
GLProgram::GLProgram() : GLObject(glCreateProgram()) {}
GLProgram::GLProgram(std::ifstream& vshader, std::ifstream& fshader) : GLProgram() {
	compileAndLink(vshader, fshader); 
}

void GLProgram::link(Shader vshader, Shader fshader) {
	GLint linked = 0; // Linked flag
	glAttachShader(handle, *vshader);
	glAttachShader(handle, *fshader);
	glLinkProgram(handle);
	glDetachShader(handle, *vshader);
	glDetachShader(handle, *fshader);
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);
	if (!linked) {
		GLint maxLength = 0;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(handle, maxLength, &maxLength, &infoLog[0]);
		throw std::runtime_error("Failed to link shaders.");
	}
}

void GLProgram::compileAndLink(std::ifstream& vshader, std::ifstream& fshader) {
	Shader vert = GLShader::VertexShader();
	Shader frag = GLShader::FragmentShader();
	vert->compile(vshader);
	frag->compile(fshader);
	link(vert, frag);
}

GLuint GLProgram::getUniformLocation(const char* unif) {
	return glGetUniformLocation(handle, unif);
}

template<typename T>
void GLProgram::setUniform(GLuint unif, T m) {}

template<>
void GLProgram::setUniform(GLuint unif, glm::mat4 m) {
	glUseProgram(handle);
	glUniformMatrix4fv(unif,
		1, GL_FALSE, glm::value_ptr(m[0]));
	glUseProgram(0);
}

template<>
void GLProgram::setUniform(GLuint unif, glm::mat3 m) {
	glUseProgram(handle);
	glUniformMatrix3fv(unif,
		1, GL_FALSE, glm::value_ptr(m[0]));
	glUseProgram(0);
}

template<>
void GLProgram::setUniform(GLuint unif, glm::vec3 v) {
	glUseProgram(handle);
	glUniform3f(unif, v[0], v[1], v[2]);
	glUseProgram(0);
}

template<>
void GLProgram::setUniform(GLuint unif, int i) {
	glUseProgram(handle);
	glUniform1i(unif, i);
	glUseProgram(0);
}

GLProgram::~GLProgram() { glDeleteProgram(handle); }

// SHADER PROGRAMS ////////////////////////////////////////////////////////////////////////////

// Camera Shader
CameraShader::CameraShader(std::ifstream& vshader, std::ifstream& fshader) 
	: GLProgram(vshader, fshader) {
	// get camera uniforms
	uModelViewMatrix = getUniformLocation("uModelViewMatrix");
	uProjectionMatrix = getUniformLocation("uProjectionMatrix");
}

void CameraShader::setModelView(glm::mat4 m) {
	setUniform(uModelViewMatrix, m);
}

void CameraShader::setProjection(glm::mat4 m) {
	setUniform(uProjectionMatrix, m);
}

// Lighting Shader
LightingShader::LightingShader(std::ifstream& vshader, std::ifstream& fshader)
	: CameraShader(vshader, fshader) {
	// get lighting uniforms
	uAmbient = getUniformLocation("uAmbient");
	uLight = getUniformLocation("uLight");
	uLightColor = getUniformLocation("uLightColor");
	uNormalMatrix = getUniformLocation("uNormalMatrix");
}

void LightingShader::setAmbient(const glm::vec3& ambient) {
	setUniform(uAmbient, ambient);
}
void LightingShader::setLight(const glm::vec3& light, glm::mat4 viewMatrix) {
	// transform light to camera coords
	glm::vec3 clight = glm::vec3(viewMatrix * glm::vec4(light, 1));
	setUniform(uLight, clight);
}

void LightingShader::setLightColor(const glm::vec3& lightColor) {
	setUniform(uLightColor, lightColor);
}

void LightingShader::setModelView(glm::mat4 m) {
	CameraShader::setModelView(m);
	glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(m)));
	setUniform(uNormalMatrix, normalMatrix);
}

void LightingShader::loadMaterial(const Material& material) {
	setAmbient(material.ambient);
}