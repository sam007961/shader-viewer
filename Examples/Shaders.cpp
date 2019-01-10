#include "Shaders.h"
static const std::string SHADER_DIR = "./Shaders/";

// Depth Shader
DepthShader::DepthShader()
	: CameraShader(
		std::ifstream(SHADER_DIR + "depth.vs"),
		std::ifstream(SHADER_DIR + "depth.fs")
	) {}

// Texture Shader
TextureShader::TextureShader()
	: TextureShader(
		std::ifstream(SHADER_DIR + "texture.vs"),
		std::ifstream(SHADER_DIR + "texture.fs")
	) {}

TextureShader::TextureShader(std::ifstream& vshader, std::ifstream& fshader)
	: CameraShader(vshader, fshader) {
	uTexture = getUniformLocation("uTexture");
};

void TextureShader::setTexture(GLuint texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	setUniform(uTexture, 0);
}

// Solid Phong Shader
PhongSolid::PhongSolid()
	: CameraShader(
		std::ifstream(SHADER_DIR + "phong.solid.vs"),
		std::ifstream(SHADER_DIR + "phong.solid.fs")
	), LightingShader(
		std::ifstream(SHADER_DIR + "phong.solid.vs"),
		std::ifstream(SHADER_DIR + "phong.solid.fs")
	) {
	uColor = getUniformLocation("uColor");
}

void PhongSolid::setColor(const glm::vec3& color) {
	setUniform(uColor, color);
}

void PhongSolid::loadMaterial(const Material& material) {
	LightingShader::loadMaterial(material);
	setColor(material.color);
}

// Texture Phong Shader
PhongTexture::PhongTexture()
	: PhongTexture(
		std::ifstream(SHADER_DIR + "phong.texture.vs"),
		std::ifstream(SHADER_DIR + "phong.texture.fs")
	) {}

PhongTexture::PhongTexture(std::ifstream& vshader, std::ifstream& fshader)
	: CameraShader(vshader, fshader),
	TextureShader(vshader, fshader),
	LightingShader(vshader, fshader) {
	uSpecularMap = getUniformLocation("uSpecularMap");
	uNormalMap = getUniformLocation("uNormalMap");
}

void PhongTexture::setSpecularMap(GLuint texture) {
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	setUniform(uSpecularMap, 1);
}

void PhongTexture::setNormalMap(GLuint texture) {
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture);
	setUniform(uNormalMap, 2);
}

void PhongTexture::loadMaterial(const Material& material) {
	LightingShader::loadMaterial(material);
	setTexture(material.textures[0]);
	setSpecularMap(material.textures[1]);
	setNormalMap(material.textures[2]);
}

// Texture Phong Shader with Shadows
PhongTextureShadow::PhongTextureShadow()
	: CameraShader(
		std::ifstream(SHADER_DIR + "phong.texture.shadow.vs"),
		std::ifstream(SHADER_DIR + "phong.texture.shadow.fs")
	), PhongTexture(
		std::ifstream(SHADER_DIR + "phong.texture.shadow.vs"),
		std::ifstream(SHADER_DIR + "phong.texture.shadow.fs")
	) {
	uShadowMap = getUniformLocation("uShadowMap");
	uModelLightSpaceMatrix = getUniformLocation("uModelLightSpaceMatrix");
}

void PhongTextureShadow::setShadowMap(GLuint texture) {
	glActiveTexture(GL_TEXTURE16);
	glBindTexture(GL_TEXTURE_2D, texture);
	setUniform(uShadowMap, 16);
}

void PhongTextureShadow::setModelLightSpaceMatrix(glm::mat4 m) {
	setUniform(uModelLightSpaceMatrix, m);
}

