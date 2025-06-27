#pragma once

#include <math.h>
#include "PerlinNoise.h"

#define DIV 5

class Noise {
public:
	static unsigned short Noise3D(float x, float y, float z);
};