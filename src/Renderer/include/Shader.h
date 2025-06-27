#pragma once


#include <glad/glad.h>
#include <string>
#include "../../glm.h"

class Shader {
private:
	unsigned int ID = 0;
public:
	Shader() {} // for declaration
	Shader(const char* vertexshaderfile, const char* fragmentshaderfile);
	void Bind();
	void Unbind();
	std::string ReadFile(const char* filename);
	void SetMat4(const char* varname, glm::mat4 data);
	void SetVec3(const char* varname, glm::vec3 data);
	void SetFloat(const char* varname, float value);
	void Delete();
	void Set1i(const char* varname, int value);
};