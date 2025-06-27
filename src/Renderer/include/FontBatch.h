#pragma once

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "../../Application/Game/Map/include/BVG.h"
#include <stdlib.h>


// For Batch Rendering

class FontBatch {
private:
	VBO* vbo = NULL;
	VAO* vao = NULL;
	EBO* ebo = NULL;
	unsigned int vertices_size = 0;
	unsigned int indices_size = 0;
public:
	unsigned int vertices_pointer = 0;
	FontBatch() {} // For declaration
	FontBatch(unsigned int vertex_buffer_size);
	void CleanVertices();
	void UpdateVertices(unsigned int offset, unsigned int size, const void* data); // update vertex_buffer
	void AddQuad(const void* data); // add quad detail in vertex_buffer 
	void Render(Shader* shader);
	void Delete();
};