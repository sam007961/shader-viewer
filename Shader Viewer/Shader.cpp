#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.h"
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

GLShader* GLShader::VertexShader() { return  new GLShader(GL_VERTEX_SHADER); }
GLShader* GLShader::FragmentShader() { return new GLShader(GL_FRAGMENT_SHADER); }

// GLPROGRAM //////////////////////////////////////////////////////////////////////////////////
GLProgram::GLProgram() : GLObject(glCreateProgram()) {}

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
LightingShader::LightingShader(const char* frag_file) : GLProgram() {

	// compile and link shaders
	GLShader* vert = GLShader::VertexShader();
	GLShader* frag = GLShader::FragmentShader();
	vert->compile(std::ifstream("./Shaders/lighting.vshader"));
	frag->compile(std::ifstream(frag_file));
	link(*vert, *frag);
	delete vert; delete frag;

	// get uniforms
	uAmbient = getUniformLocation("uAmbient");
	uLight = getUniformLocation("uLight");
	uLightColor = getUniformLocation("uLightColor");

	// get camera uniforms
	uModelViewMatrix = getUniformLocation("uModelViewMatrix");
	uProjectionMatrix = getUniformLocation("uProjectionMatrix");
	uNormalMatrix = getUniformLocation("uNormalMatrix");
}

void LightingShader::setAmbient(const glm::vec3& ambient) {
	setUniform(uAmbient, ambient);
}
void LightingShader::setLight(const glm::vec3& light, glm::mat4 view) {
	glm::vec3 clight = glm::vec3(view * glm::vec4(light, 1));
	setUniform(uLight, clight);
}

void LightingShader::setLightColor(const glm::vec3& lightColor) {
	setUniform(uLightColor, lightColor);
}

void LightingShader::setModelView(glm::mat4 m) {
	setUniform(uModelViewMatrix, m);
	glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(m)));
	setUniform(uNormalMatrix, normalMatrix);
}

void LightingShader::setProjection(glm::mat4 m) {
	setUniform(uProjectionMatrix, m);
}

void LightingShader::loadMaterial(const Material& material) {
	setAmbient(material.ambient);
}

PhongSolid::PhongSolid() : LightingShader("./Shaders/phong_solid.fshader") {
	uColor = getUniformLocation("uColor");
}

void PhongSolid::setColor(const glm::vec3& color) {
	setUniform(uColor, color);
}

void PhongSolid::loadMaterial(const Material& material) {
	LightingShader::loadMaterial(material);
	setColor(material.color);
}

PhongTexture::PhongTexture() : LightingShader("./Shaders/phong_texture.fshader") {
	uTexture = getUniformLocation("uTexture");
}

void PhongTexture::setTexture(GLuint texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	setUniform(uTexture, 0);
}

void PhongTexture::loadMaterial(const Material& material) {
	LightingShader::loadMaterial(material);
	setTexture(material.textures[0]);
}