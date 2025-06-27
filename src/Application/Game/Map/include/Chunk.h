#pragma once

#include "../../../../Renderer/include/Camera.h"
#include "Noise.h"

#define CHUNK_X_LENGTH 16
#define CHUNK_Y_LENGTH 48
#define CHUNK_Z_LENGTH 16


#define visibled 45.0f

class Chunk {
private:
	glm::vec4 a;
	unsigned short m_array[CHUNK_Z_LENGTH][CHUNK_Y_LENGTH][CHUNK_X_LENGTH] = { 0 };
public:
	bool isready = false;
	bool m_isChanged = true;
	long m_offsetx = 0;
	long m_offsety = 0;
	long m_offsetz = 0;
	Chunk() {} // for declaration
	Chunk(long offsetx, long offsety, long offsetz);
	unsigned short get(unsigned char x, unsigned char y, unsigned char z);
	void set(unsigned char x, unsigned char y, unsigned char z, unsigned short value);
	void Reset(long offsetx, long offsety, long offsetz);
	double getAngle(glm::vec3 pos);
	double getMagnitude(glm::vec3 value);
	bool isVisibletoCamera();
	void Delete();
};