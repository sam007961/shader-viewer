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

GLShader* GLShader::VertexShader() { return  new GLShader(GL_VERTEX_SHADER); }
GLShader* GLShader::FragmentShader() { return new GLShader(GL_FRAGMENT_SHADER); }

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

GLProgram::operator GLuint() const { return handle; }

GLProgram::~GLProgram() { glDeleteProgram(handle); }

// SHADER PROGRAMS ////////////////////////////////////////////////////////////////////////////
PhongShader::PhongShader() : GLProgram() {

	// compile and link shaders
	GLShader* vert = GLShader::VertexShader();
	GLShader* frag = GLShader::FragmentShader();
	vert->compile(std::ifstream("./shaders/basic.vshader"));
	frag->compile(std::ifstream("./shaders/phong.fshader"));
	link(*vert, *frag);
	delete vert; delete frag;

	// get uniforms
	uAlbedo = getUniformLocation("uAlbedo");
	uAmbient = getUniformLocation("uAmbient");
	uLight = getUniformLocation("uLight");

	// get camera uniforms
	uModelViewMatrix = getUniformLocation("uModelViewMatrix");
	uProjectionMatrix = getUniformLocation("uProjectionMatrix");
}

void PhongShader::setAlbedo(const glm::vec3& albedo) {
	glUseProgram(*this);
	glUniform3f(uAlbedo, albedo[0], albedo[1], albedo[2]);
	glUseProgram(0);
}
void PhongShader::setAmbient(const glm::vec3& ambient) {
	glUseProgram(*this);
	glUniform3f(uAmbient, ambient[0], ambient[1], ambient[2]);
	glUseProgram(0);
}
void PhongShader::setLight(const glm::vec3& light) {
	glUseProgram(*this);
	glUniform3f(uLight, light[0], light[1], light[2]);
	glUseProgram(0);
}

void PhongShader::setModelView(glm::mat4 m) {
	setUniform(uModelViewMatrix, m);
}

void PhongShader::setProjection(glm::mat4 m) {
	setUniform(uProjectionMatrix, m);
}