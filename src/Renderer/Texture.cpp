#include "include/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* filename, unsigned int type) {
	glGenTextures(1, &ID);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int x, y, comp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &x, &y, &comp, 0);


	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, type, x, y, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);
}


void Texture::Delete() {
	glDeleteTextures(1, &ID);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::get() {
	return ID;
}