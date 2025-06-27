#pragma once

#include "../../../../Renderer/include/VBO.h"
#include "../../../../Renderer/include/VAO.h"
#include "../../../../Renderer/include/EBO.h"
#include "../../../../Renderer/include/Shader.h"

#define GTPX 1.0f/1024
#define GTPY 1.0f/1024

class Block3D {
private:
	VBO* vbo = NULL;
	VAO* vao = NULL;
	EBO* ebo = NULL;
	float vertices[192] = { 0.0f };
	int indices[36] = {
		0,1,2,		0,2,3,
		4,5,6,		4,6,7,
		8,9,10,		8,10,11,
		12,13,14,	12,14,15,
		16,17,18,	16,18,19,
		20,21,22,	20,22,23
	};
public:
	Block3D() {} // for declaration
	Block3D(float firstx, float lastx, float firsty, float lasty, float firstz, float lastz);
	void SetTextureCoordinates(int side, float x1, float y1, float x2, float y2);
	void GenerateBlock3D();
	void Render(Shader* shader, glm::vec3 position, float deg, glm::vec3 rotateaxis);
	void Render(Shader* shader, glm::vec3 position);
	void Delete();
};