#include "include/Box2D.h"

Box2D::Box2D(float x, float y, float width, float height, float tx1, float ty1, float tx2, float ty2) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	float vertices[] = {
		0.0f,		0.0f,		0.0f,		tx1,		ty1,
		width,		0.0f,		0.0f,		tx2,		ty1,
		width,		-height,	0.0f,		tx2,		ty2,
		0.0f,		-height,	0.0f,		tx1,		ty2
	};

	unsigned int indices[] = {
		0,1,2,	0,2,3
	};

	vbo = new VBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
	vao = new VAO();
	vao->LinkVBO(vbo, 0, 3, 5 * sizeof(float), 0);
	vao->LinkVBO(vbo, 1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao->Bind();
	ebo = new EBO(sizeof(indices), indices, GL_STATIC_DRAW);
}

void Box2D::Render(Shader* shader) {
	vao->Bind();
	ebo->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0.0f));
	shader->Bind();
	shader->SetMat4("model", model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Box2D::Render(Shader* shader, float x, float y) {
	this->x = x;
	this->y = y;
	Render(shader);
}



void Box2D::Render(Shader* shader, float opacity) {
	shader->Bind();
	shader->SetFloat("opacity", opacity);
	Render(shader);
}

void Box2D::Delete() {
	vbo->Delete();
	vao->Delete();
	ebo->Delete();
	delete vbo;
	delete vao;
	delete ebo;
}

float Box2D::getX() {
	return x;
}

float Box2D::getY() {
	return y;
}

float Box2D::getWidth() {
	return width;
}

float Box2D::getHeight() {
	return height;
}