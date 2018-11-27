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
	Shader(GLenum shaderType);
	Shader(GLenum shaderType, const char* source);
	Shader(GLenum shaderType, const std::vector<char>& source);
	Shader(GLenum shaderType, std::ifstream& source);

	// Store GLSL source code in shader object and compile it
	void compile(const char* source);
	void compile(std::ifstream& source);

	~Shader();

	operator GLuint() const;
};

class GLProgram {
private:
	const GLuint handle;

public:
	handle_map attr;   // Attribute handles
	handle_map unif;   // Uniform handles

	GLProgram(Shader vs, Shader fs);

	// Attach shaders to program and link
	void link(const Shader& vs, const Shader& fs);

	~GLProgram();

	operator GLuint();
};


class GLTarget {
private:
	GLuint out; //
public:

};
#define GLINPUT(prog, list) { GLProgram* _PROG = &(prog); list; } void _DUMMY_SHADER_H()
#define ATTR(name) _PROG->attr[#name] = glGetAttribLocation (*_PROG, #name);
#define UNIF(name) _PROG->unif[#name] = glGetUniformLocation(*_PROG, #name);
#define GLSL(source) #source