#pragma once

#include "../../include/Door.h"
#include <mutex>

class DoorManager {
public:
	static std::mutex mut;
	static std::vector<Door*> manager;
	static void addDoor(long x, long y, long z, bool is_on_x_axis, bool is_on_positive_side);
	static void removeDoor(long x, long y, long z);
	static bool isCollide(AABB aabb);
};