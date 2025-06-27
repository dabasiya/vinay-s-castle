#pragma once

#include <glad/glad.h>

class EBO {
private:
	unsigned int ID = 0;
public:
	EBO() {} // for declaration
	EBO(unsigned int size, const void* data, GLenum usage);
	void Bind();
	void Unbind();
	void Update(unsigned int offset, unsigned int size, const void* data);
	void Delete();
};