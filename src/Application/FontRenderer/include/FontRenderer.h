#pragma once

#include "../../../Renderer/include/Texture.h"
#include "../../../Renderer/include/VBO.h"
#include "../../../Renderer/include/EBO.h"
#include "../../../Renderer/include/VAO.h"
#include "../../../Renderer/include/Shader.h"
#include "../../../Renderer/include/Window.h"
#include "../../../Renderer/include/FontBatch.h"
#include <string>

class FontRenderer {
private:
	static int FontWidth[256];
	Texture* texture = NULL;
	Shader* shader = NULL;
	static float pixelx;
	FontBatch* m_batch = NULL;
	std::string temp_str = "";
	float temp_scale = 0.0f;
public:
	static float* data;
	FontRenderer();
	void PrintString(std::string str, float x, float y, float scale);
	void PrintString(std::string str, float x, float y, float scale, float degree, glm::vec3 rotationaxis);
	void Delete();
	void Free();
	static unsigned int getStringPixelWidth(std::string str);
	static float* getFontVertices(unsigned char ch, float startx, float starty, float scale);
};