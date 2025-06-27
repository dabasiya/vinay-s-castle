#pragma once

#include <glad/glad.h>

class Texture {
private:
	unsigned int ID = 0;
public:
	Texture() {} // for declaration
	Texture(const char* filename, unsigned int type);
	void Delete();
	void Bind();
	void Unbind();
	unsigned int get();
};