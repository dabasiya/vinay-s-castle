
#include "include/AABB.h"
#include <iostream>

AABB::AABB(float x, float y, float z, float x_length, float y_length, float z_length) {
	m_x = x;
	m_y = y;
	m_z = z;
	m_x_length = x_length;
	m_y_length = y_length;
	m_z_length = z_length;
}

bool AABB::overlap(AABB a, AABB b) {
	if(((a.m_x + a.m_x_length >= b.m_x && a.m_x + a.m_x_length <= b.m_x + b.m_x_length) || (a.m_x >= b.m_x && a.m_x <= b.m_x + b.m_x_length) || (a.m_x < b.m_x && a.m_x+a.m_x_length > b.m_x + b.m_x_length)) &&
		((a.m_y + a.m_y_length >= b.m_y && a.m_y + a.m_y_length <= b.m_y + b.m_y_length) || (a.m_y >= b.m_y && a.m_y <= b.m_y + b.m_y_length) || (a.m_y < b.m_y && a.m_y + a.m_y_length > b.m_y + b.m_y_length)) &&
		((a.m_z + a.m_z_length >= b.m_z && a.m_z + a.m_z_length <= b.m_z + b.m_z_length) || (a.m_z >= b.m_z && a.m_z <= b.m_z + b.m_z_length) || (a.m_z < b.m_z && a.m_z + a.m_z_length > b.m_z + b.m_z_length))) {
		return true;
	}
	return false;
}



bool AABB::overlap_with_map() {
	long x = floor(m_x);
	long y = floor(m_y);
	long z = floor(m_z);
	long x_length = floor(m_x_length);
	long y_length = floor(m_y_length);
	long z_length = floor(m_z_length);

	ChunkManager::mut.lock();
	if (ChunkManager::get(x, y, z) != 0 ||
		ChunkManager::get(x + x_length, y, z) != 0 ||
		ChunkManager::get(x, y + y_length, z) != 0 ||
		ChunkManager::get(x, y, z + z_length) != 0 ||
		ChunkManager::get(x + x_length, y + y_length, z) != 0 ||
		ChunkManager::get(x, y + y_length, z + z_length) != 0 ||
		ChunkManager::get(x + x_length, y, z + z_length) != 0 ||
		ChunkManager::get(x + x_length, y + y_length, z + z_length)) {
		ChunkManager::mut.unlock();
		return true;
	}
	else {
		ChunkManager::mut.unlock();
		return false;
	}
}

bool AABB::overlap_with_map_x() {
	long x = floor(m_x);
	long y = floor(m_y);
	long z = floor(m_z);
	long x_length = floor(m_x_length);
	long y_length = floor(m_y_length);

	ChunkManager::mut.lock();
	if (ChunkManager::get(x, y+y_length, z) != 0 ||
		ChunkManager::get(x + x_length, y+y_length, z) != 0) {
		ChunkManager::mut.unlock();
		return true;
	}
	else {
		ChunkManager::mut.unlock();
		return false;
	}
}


bool AABB::overlap_with_map_y() {
	long x = floor(m_x);
	long y = floor(m_y);
	long z = floor(m_z);
	long y_length = floor(m_y_length);

	ChunkManager::mut.lock();
	if (ChunkManager::get(x, y, z) != 0 ||
		ChunkManager::get(x, y+y_length, z) != 0) {
		ChunkManager::mut.unlock();
		return true;
	}
	else {
		ChunkManager::mut.unlock();
		return false;
	}
}



bool AABB::overlap_with_map_z() {
	long x = floor(m_x);
	long y = floor(m_y);
	long z = floor(m_z);
	long z_length = floor(m_z_length);
	long y_length = floor(m_y_length);

	ChunkManager::mut.lock();
	if (ChunkManager::get(x, y+y_length, z) != 0 ||
		ChunkManager::get(x, y+y_length, z + z_length) != 0) {
		ChunkManager::mut.unlock();
		return true;
	}
	else {
		ChunkManager::mut.unlock();
		return false;
	}
}

glm::vec3 AABB::getPosition() {
	return glm::vec3(m_x, m_y, m_z);
}

glm::vec3 AABB::getSize() {
	return glm::vec3(m_x_length, m_y_length, m_z_length);
}

