#pragma once
#include <fstream>
#include <GL\glew.h>
#include <glm/common.hpp>
#include <memory>

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
	static std::shared_ptr<GLShader> VertexShader();
	static std::shared_ptr<GLShader> FragmentShader();
};
typedef std::shared_ptr<GLShader> Shader;

// base program class
class GLProgram : public GLObject {
protected:
	GLProgram();
	GLProgram(std::ifstream&, std::ifstream&);
	// helpers for constructing shader
	void link(Shader vshader, Shader fshader);
	void compileAndLink(std::ifstream& vshader, std::ifstream& fshader);
	GLuint getUniformLocation(const char* unif);

	// helpers for setting uniforms
	template<typename T>
	void setUniform(GLuint unif, T m);

public:
	virtual ~GLProgram();
};

// camera shader class
class CameraShader : public GLProgram {
private:
	// Camera
	GLuint uModelViewMatrix, uProjectionMatrix;

protected:
	CameraShader(std::ifstream& vshader, std::ifstream& fshader);

public:
	void setModelView(glm::mat4 m); // set modelViewMatrix
	void setProjection(glm::mat4 m); // set projectionMatrix
};

// depth shader class
class DepthShader : public CameraShader {
public:
	DepthShader();
};

// texture shader class
class TextureShader : virtual public CameraShader {
private:
	// Texture
	GLuint uTexture;

protected:
	TextureShader(std::ifstream& vshader, std::ifstream& fshader);

public:
	TextureShader();
	void setTexture(GLuint texture);
};

// lighting shader class
class LightingShader : public virtual CameraShader {
private:
	// Ambient Light | Light Direction | Light Color
	GLuint uAmbient, uLight, uLightColor;

	// normal transformation matrix
	GLuint uNormalMatrix;

protected:
	LightingShader(std::ifstream& vshader, std::ifstream& fshader);

public:
	void setAmbient(const glm::vec3& ambient); // set ambient light
	void setLight(const glm::vec3& light, glm::mat4 viewMatrix=glm::mat4(1)); // set light position/direction
	void setLightColor(const glm::vec3& lightColor); // set light color
	void setModelView(glm::mat4 m); // set modelViewMatrix and automatically set normalMatrix

	virtual void loadMaterial(const Material& material); // load uniforms from material
};

// solid color phong shader
class PhongSolid : public LightingShader {
private:
	// Color
	GLuint uColor;

public:
	PhongSolid();
	void setColor(const glm::vec3& color);
	virtual void loadMaterial(const Material& material);
};

// texture phong shader
class PhongTexture : public TextureShader, public LightingShader {
private:
	//GLuint uTexture;
	GLuint uSpecularMap;
	GLuint uNormalMap;

protected:
	PhongTexture(std::ifstream& vshader, std::ifstream& fshader);

public:
	PhongTexture();
	void setSpecularMap(GLuint texture);
	void setNormalMap(GLuint texture);
	virtual void loadMaterial(const Material& material);
};


// texture phong shader with shadow
class PhongTextureShadow : public PhongTexture {
private:
	GLuint uShadowMap;
	GLuint uModelLightSpaceMatrix;

public:
	PhongTextureShadow();
	void setShadowMap(GLuint texture);
	void setModelLightSpaceMatrix(glm::mat4 m);
};