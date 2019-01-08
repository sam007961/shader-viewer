#include "Framebuffer.h"

GLFramebuffer::GLFramebuffer() { glGenFramebuffers(1, &handle); }
void GLFramebuffer::clear() { 
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
GLFramebuffer::~GLFramebuffer() { glDeleteFramebuffers(1, &handle); }