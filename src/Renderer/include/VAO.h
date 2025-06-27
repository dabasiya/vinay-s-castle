#pragma once

#include "VBO.h"

class VAO {
private:
	unsigned int ID = 0;
public:
	VAO();
	void Bind();
	void Unbind();
	void LinkVBO(VBO *vbo, unsigned int index, unsigned int dim_size, unsigned int stride_size, const void* ptr);
	void Delete();
};