#include "include/VBO.h"

VBO::VBO(unsigned int datasize, const void* data, GLenum usage) {
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, datasize, data, usage);
	Unbind();
}


void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Update(unsigned int offset, unsigned int size, const void* data) {
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	Unbind();
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}