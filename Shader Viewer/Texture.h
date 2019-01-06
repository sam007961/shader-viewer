#pragma once
#include "GLObject.h"

// base texture class
class GLTexture : public GLObject {
protected:
	typedef unsigned char byte;
	virtual void setup(GLuint format, byte* data, int width, int height, int nChannels) = 0;
public:
	GLTexture();
	virtual ~GLTexture();
	void loadData(GLuint format, const char* path);
};

// 2D texture
class GLTexture2D : public GLTexture {
protected:
	typedef unsigned char byte;
	virtual void setup(GLuint format, byte* data, int width, int height, int nChannels);

public:
	void setWrapS(GLenum param) { /*TODO*/; }
	void setWrapT(GLenum param) { /*TODO*/; }
	void setMinFilter(GLenum param) { /*TODO*/; }
	void setMagFilter(GLenum param) { /*TODO*/; }
};