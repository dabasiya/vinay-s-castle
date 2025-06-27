#pragma once

#include "../../../Renderer/include/VAO.h"
#include "../../../Renderer/include/VBO.h"
#include "../../../Renderer/include/EBO.h"
#include "../../../Renderer/include/Shader.h"

class Box2D {
private:
	VBO* vbo = NULL;
	VAO* vao = NULL;
	EBO* ebo = NULL;
	float x = 0.0f;
	float y = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
public:
	Box2D() {} // for declaration
	Box2D(float x, float y, float width, float height, float tx1, float ty1, float tx2, float ty2);
	void Render(Shader* shader);
	void Render(Shader* shader, float x, float y);
	void Render(Shader* shader, float opacity);
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	void Delete();
};