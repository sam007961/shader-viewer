#pragma once
#include "GLObject.h"
#include "Framebuffer.h"

// base texture class
class GLTexture : public GLObject {
protected:
	typedef unsigned char byte;
	virtual void setup(GLuint format, byte* data, int width, int height, int nChannels) = 0;
public:
	GLTexture();
	virtual ~GLTexture();
	void loadData(GLuint format, const char* path);
	virtual void attachDepthBuffer(const GLFramebuffer& fbo, unsigned int width, unsigned int height) = 0;
};

// 2D texture
class GLTexture2D : public GLTexture {
protected:
	virtual void setup(GLuint format, byte* data, int width, int height, int nChannels);

public:
	virtual void attachDepthBuffer(const GLFramebuffer& fbo, unsigned int width, unsigned int height);
	void setWrapS(GLenum param) { /*TODO*/; }
	void setWrapT(GLenum param) { /*TODO*/; }
	void setMinFilter(GLenum param) { /*TODO*/; }
	void setMagFilter(GLenum param) { /*TODO*/; }
};