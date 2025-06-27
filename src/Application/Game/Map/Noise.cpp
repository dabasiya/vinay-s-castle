#include "include/Noise.h"
#include "include/PerlinNoise.h"
#include <stdint.h>

unsigned short Noise::Noise3D(float x, float y, float z) {
	if ((unsigned int)y == 0 || (unsigned int)y == 48-1)
		return 2;

	/*
	float height = 50 + 200 * PerlinNoise::noise(x/DIV, z/DIV, 4);
	if (y < height)
		return 1;
	*/

	if (y == 10)
		return 1;

	if (y < 48) {
		if ((int)x % 16 == 0 || (int)z%16 == 0) {
			x = (int)(x / 16);
			z = (int)(z / 16);
			double x1 = PerlinNoise::noise(x / DIV, z / DIV, 4) * 255;
			double x2 = PerlinNoise::noise((x / DIV) - 1, z / DIV, 4) * 255;
			double y1 = PerlinNoise::noise((x / DIV), z / DIV, 4) * 255;
			double y2 = PerlinNoise::noise((x / DIV), (z/ DIV)-1, 4) * 255;

			if ((x1 > 60 && x2 < 60) || (x1 < 60 && x2 > 60) || (y1 > 60 && y2 < 60) || (y1 < 60 && y2 > 60))
				return 1;

		}
	}

	return 0;
}
