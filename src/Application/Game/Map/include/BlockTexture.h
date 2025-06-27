#pragma once

#include <vector> 

#define ax_pixel (1.0f/1024)
#define ay_pixel (1.0f/1024)

enum texturecoords {
	AIR_BLOCK, 
	WOOD_BLOCK,
	UNBREAKABLE_BLOCK
};

std::vector<std::vector<float>> texcoords = {
	{0.0f, 0.0f, 0.0f, 0.0f},											// air block
	{0.0f, 1.0f - (ay_pixel*1008), 16 * ax_pixel, 0.0f},				// wood block
	{16*ax_pixel, 1.0f - (ay_pixel*1008), 32*ax_pixel, 0.0f},			// unbreakable block texture
};	