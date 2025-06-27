#include "include/EBO.h"

EBO::EBO(unsigned int size, const void* data, GLenum usage) {
	glGenBuffers(1, &ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	Unbind();
}


void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Update(unsigned int offset, unsigned int size, const void* data) {
	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	Unbind();
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}