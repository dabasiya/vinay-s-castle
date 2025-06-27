#pragma once

#include <glad/glad.h>
#include <iostream>

class FBO {
private:
	unsigned int ID = 0;
	unsigned int texture = 0;
public:
	//FBO() {} // for declaration
	FBO();
	void Bind();
	void Unbind();
	void Delete();
};