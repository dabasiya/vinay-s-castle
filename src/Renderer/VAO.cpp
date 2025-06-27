#include "include/VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::LinkVBO(VBO *vbo, unsigned int index, unsigned int dim_size, unsigned int stride_size, const void* ptr) {
	vbo->Bind();
	Bind();
	glVertexAttribPointer(index, dim_size, GL_FLOAT, GL_FALSE, stride_size, ptr);
	glEnableVertexAttribArray(index);
	Unbind();
	vbo->Unbind();
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}