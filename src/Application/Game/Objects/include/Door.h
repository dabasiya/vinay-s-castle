#pragma once


#include "../../Physics/include/AABB.h"
#include "../../Map/include/BVG.h"
#include <thread>

#define ax_pixel 1.0f/1024
#define ay_pixel 1.0f/1024

class Door {
public:
	AABB m_aabb;
	long x = 0;
	long y = 0;
	long z = 0;
	bool is_on_x_axis = true;
	bool is_on_positive_side = true;
	bool canchangestate = true;
	bool isOpen = false;
	std::thread statechangethread;
	Door(bool is_on_x_axis, bool is_on_positive_side, long x, long y, long z);
	static void copy(std::vector<float>& v1, std::vector<float>& v2);
	std::vector<float> getVertices();
	void setAABB(bool is_on_x_axis, bool is_on_positive_side);
	static bool isCollide(AABB aabb1, AABB aabb2);
	void changestate();
	void delayafterstatechange();
};