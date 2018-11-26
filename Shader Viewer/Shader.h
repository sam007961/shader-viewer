#pragma once
#include <GL\glew.h>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

typedef std::unordered_map < std::string, GLuint > handle_map;

class Shader {
private:
	const GLuint handle; // GLSL program handle

public:
	// Create shader object of type shaderType
	Shader(GLenum shaderType=GL_VERTEX_SHADER) : handle(glCreateShader(shaderType)) {
		if (!handle) {
			throw std::runtime_error("Failed to create shader object.");
		}
	}

	Shader(GLenum shaderType, const char* source) : Shader(shaderType) {
		compile(source);
	}

	Shader(GLenum shaderType, const std::vector<char>& source) : Shader(shaderType) {
		compile(&source[0]);
	}

	Shader(GLenum shaderType, std::ifstream& source) : Shader(shaderType) {
		compile(source);
	}

	// Store GLSL source code in shader object and compile it
	void compile(const char* source) {

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

	void compile(std::ifstream& source) {
		std::vector<char> temp;
		source.seekg(0, std::ios_base::end);
		std::streampos fileSize = source.tellg();
		temp.resize(fileSize);

		source.seekg(0, std::ios_base::beg);
		source.read(&temp[0], fileSize);

		compile(&temp[0]);
	}

	~Shader() {
		glDeleteShader(handle);
	}

	operator GLuint() const{
		return handle;
	}
};

class GLProgram {
private:
	const GLuint handle;

public:
	handle_map attr;   // Attribute handles
	handle_map unif;   // Uniform handles

	GLProgram(Shader vs, Shader fs) : handle(glCreateProgram()) {
		if (handle == 0)
			throw std::runtime_error("glCreateProgram fails");
		link(vs, fs);
		glBindFragDataLocation(handle, 0, "fragColor");
	}

	// Attach shaders to program and link
	void link(const Shader& vs, const Shader& fs) {
		GLint linked = 0; // Linked flag
		glAttachShader(handle, vs);
		glAttachShader(handle, fs);
		glLinkProgram(handle);
		glDetachShader(handle, vs);
		glDetachShader(handle, fs);
		glGetProgramiv(handle, GL_LINK_STATUS, &linked);
		if (!linked)
			throw std::runtime_error("Failed to link shaders.");
	}

	~GLProgram() {
		glDeleteProgram(handle);
	}

	operator GLuint() {
		return handle;
	}

};

#define GLINPUT(prog, list) { GLProgram* _PROG = &(prog); list; } void _DUMMY_SHADER_H()

#define ATTR(name) _PROG->attr[#name] = glGetAttribLocation (*_PROG, #name);
#define UNIF(name) _PROG->unif[#name] = glGetUniformLocation(*_PROG, #name);


#define GLSL(source) #source