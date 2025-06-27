#include "include/Batch.h"
#include <iostream>

Batch::Batch(unsigned int vertex_buffer_size) {
	unsigned int indices_count = (unsigned int)(vertex_buffer_size / (sizeof(float) * 56)) * 6;
	unsigned int* indices = (unsigned int*)malloc(indices_count * sizeof(unsigned int));
	indices_size = indices_count;

	int a = 0;
	unsigned int b = 0;
	for (int i = 0; i < indices_count/6; i++) {
		a = i * 6;
		b = i * 4;
		indices[a] = b;
		indices[a + 1] = b + 1;
		indices[a + 2] = b + 2;

		indices[a + 3] = b;
		indices[a + 4] = b + 2;
		indices[a + 5] = b + 3;
	}

	vbo = new VBO(vertex_buffer_size, 0, GL_DYNAMIC_DRAW);
	vao = new VAO();
	vao->LinkVBO(vbo, 0, 3, 14 * sizeof(float), 0);
	vao->LinkVBO(vbo, 1, 3, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	vao->LinkVBO(vbo, 2, 2, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	vao->LinkVBO(vbo, 3, 3, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	vao->LinkVBO(vbo, 4, 3, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	vao->Bind();
	ebo = new EBO(indices_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	vertices_size = vertex_buffer_size;
	vertices_pointer = 0;
	free(indices);
}

void Batch::UpdateVertices(unsigned int offset, unsigned int size, const void* data) {
	vbo->Update(offset, size, data);
	vertices_pointer += size;
}

void Batch::Render(Shader* shader) {
	vbo->Bind();
	vao->Bind();
	ebo->Bind();
	shader->Bind();
	glDrawElements(GL_TRIANGLES, (vertices_pointer/(56*sizeof(float)))*6, GL_UNSIGNED_INT, 0);
}

void Batch::AddQuad(const void* data) {
	UpdateVertices(vertices_pointer, 56 * sizeof(float), data);
}


void Batch::Delete() {
	vbo->Delete();
	vao->Delete();
	ebo->Delete();
	delete vbo;
	delete vao;
	delete ebo;
}

void Batch::CleanVertices() {
	vbo->Update(0, vertices_size, NULL);
	vertices_pointer = 0;
}

