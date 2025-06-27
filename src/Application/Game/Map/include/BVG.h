#pragma once

// BVG stands for Block Vertices Generator

#include <stdlib.h>
#include <string.h>
#include <vector>

enum Block3D_Side {
	Z_NEGATIVE,
	X_POSITIVE,
	Z_POSITIVE,
	X_NEGATIVE,
	Y_NEGATIVE,
	Y_POSITIVE
};

class BVG {
public:
	static std::vector<float> GetBlockVertices(unsigned int side, float x, float y, float z, float tx1, float ty1, float tx2, float ty2);
	static std::vector<float> GetBlockVertices(unsigned int side, float x, float y, float z, float x_length, float y_length, float z_length, float tx1, float ty1, float tx2, float ty2);
};