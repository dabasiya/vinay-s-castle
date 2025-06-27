#pragma once

// for collision detection

#include "../../../../glm.h"
#include "../../Map/include/ChunkManager.h"

class AABB {
private:
	// position and length variable
	float m_x_length = 0.0f;
	float m_y_length = 0.0f;
	float m_z_length = 0.0f;
public:
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
	AABB() {} // for declaration
	AABB(float x, float y, float z, float x_length, float y_length, float z_length);
	static bool overlap(AABB a, AABB b);
	bool overlap_with_map();
	bool overlap_with_map_x();	// check collision of x axis
	bool overlap_with_map_z();	// check collision of z axis
	bool overlap_with_map_y();	// check collide y axis
	glm::vec3 getPosition();
	glm::vec3 getSize();
};