#include "include/Block3D.h"
#include <iostream>


Block3D::Block3D(float firstx, float lastx, float firsty, float lasty, float firstz, float lastz) {
	
	// vertices for 3d block

	float vertices1[] = {

		// z negative side
		firstx,		firsty,		firstz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		firstx,		lasty,		firstz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		lastx,		lasty,		firstz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		lastx,		firsty,		firstz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,

		// x positive side
		lastx,		firsty,		firstz,		1.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		lastx,		lasty,		firstz,		1.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		lastx,		lasty,		lastz,		1.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		lastx,		firsty,		lastz,		1.0f,		0.0f,		0.0f,		0.0f,		0.0f,

		// z positive side
		lastx,		firsty,		lastz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		lastx,		lasty,		lastz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		firstx,		lasty,		lastz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		firstx,		firsty,		lastz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,

		// x negative side
		firstx,		firsty,		lastz,		-1.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		firstx,		lasty,		lastz,		-1.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		firstx,		lasty,		firstz,		-1.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		firstx,		firsty,		firstz,		-1.0f,		0.0f,		0.0f,		0.0f,		0.0f,

		// y negative side
		firstx,		firsty,		firstz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		lastx,		firsty,		firstz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		lastx,		firsty,		lastz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		firstx,		firsty,		lastz,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,

		// y positive side
		firstx,		lasty,		firstz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		firstx,		lasty,		lastz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		lastx,		lasty,		lastz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		lastx,		lasty,		firstz,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f
	};

	memcpy(vertices, vertices1, 192 * sizeof(float));
}


// set texture coordinates for sides of 3d box
void Block3D::SetTextureCoordinates(int side, float x1, float y1, float x2, float y2) {

	vertices[32 * side + 6] = x2;
	vertices[32 * side + 7] = y2;

	vertices[32 * side + 8 + 6] = x2;
	vertices[32 * side + 8 + 7] = y1;

	vertices[32 * side + 16 + 6] = x1;
	vertices[32 * side + 16 + 7] = y1;

	vertices[32 * side + 24 + 6] = x1;
	vertices[32 * side + 24 + 7] = y2;
}

void Block3D::GenerateBlock3D() {
	vbo = new VBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
	vao = new VAO();
	vao->LinkVBO(vbo, 0, 3, 8 * sizeof(float), 0);
	vao->LinkVBO(vbo, 1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao->LinkVBO(vbo, 2, 2, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao->Bind();
	ebo = new EBO(sizeof(indices), indices, GL_STATIC_DRAW);
}

void Block3D::Render(Shader* shader, glm::vec3 position) {
	Render(shader, position, 0.0f, glm::vec3(1.0f));
}

void Block3D::Render(Shader* shader, glm::vec3 position, float deg, glm::vec3 rotateaxis) {
	glm::mat4 positionmat = glm::mat4(1.0f);
	positionmat = glm::translate(positionmat, position);
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation = glm::rotate(rotation, glm::radians(deg), rotateaxis);
	vao->Bind();
	ebo->Bind();
	shader->Bind();
	shader->SetMat4("position",positionmat);
	shader->SetMat4("rotation", rotation);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}



void Block3D::Delete() {
	vao->Delete();
	vbo->Delete();
	ebo->Delete();
	delete vao;
	delete vbo;
	delete ebo;
}