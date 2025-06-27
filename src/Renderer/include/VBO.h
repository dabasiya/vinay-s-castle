#pragma once

#include <glad/glad.h>

class VBO {
private:
	unsigned int ID = 0;
public:
	VBO() {} // for declaration
	VBO(unsigned int datasize, const void* data, GLenum usage);
	void Bind();
	void Unbind();
	void Update(unsigned int offset, unsigned int size, const void* data);
	void Delete();
};