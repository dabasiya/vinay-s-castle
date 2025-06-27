#include "include/Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>


Shader::Shader(const char* vertexshaderfile, const char* fragmentshaderfile) {
	ID = glCreateProgram();

	std::string vertexshaderstring, fragmentshaderstring;
	vertexshaderstring = ReadFile(vertexshaderfile);
	fragmentshaderstring = ReadFile(fragmentshaderfile);
	const char* vertexshaderchar = vertexshaderstring.c_str();
	const char* fragmentshaderchar = fragmentshaderstring.c_str();


	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexshaderchar, NULL);
	glCompileShader(vertex);

	GLint shadercompiled;

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &shadercompiled);

	if (shadercompiled == GL_FALSE) {
		printf("vertex compile error\n");
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentshaderchar, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &shadercompiled);

	if (shadercompiled == GL_FALSE) {
		printf("fragment compile error\n");
	}

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);


	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::Bind() {
	glUseProgram(ID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

std::string Shader::ReadFile(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if(in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

void Shader::SetMat4(const char* varname, glm::mat4 data) {
	glUniformMatrix4fv(glGetUniformLocation(ID, varname), 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::SetVec3(const char* varname, glm::vec3 data) {
	glUniform3fv(glGetUniformLocation(ID, varname), 1, glm::value_ptr(data));
}

void Shader::SetFloat(const char* varname, float value) {
	glUniform1fv(glGetUniformLocation(ID, varname), 1, &value);
}

void Shader::Set1i(const char* varname, int value) {
	glUniform1i(glGetUniformLocation(ID, varname), value);
}