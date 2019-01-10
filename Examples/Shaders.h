#pragma once
#include <Shader.h>

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