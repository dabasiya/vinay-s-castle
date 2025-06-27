#include "include/DoorManager.h"

std::vector<Door*> DoorManager::manager;
std::mutex DoorManager::mut;



void DoorManager::addDoor(long x, long y, long z, bool is_on_x_axis, bool is_on_positive_side) {
	manager.push_back(new Door(is_on_x_axis, is_on_positive_side, x, y, z));
}

void DoorManager::removeDoor(long x, long y, long z) {
	int index = 0;
	bool found = false;
	while (!found) {
		if (manager[index]->x == x && manager[index]->y == y && manager[index]->z == z)
			found = true;
		index++;
	}
	delete manager[index];
	manager.erase(manager.begin() + index);
}

bool DoorManager::isCollide(AABB aabb) {
	for (int i = 0; i < manager.size(); i++) {
		bool check = manager[i]->isCollide(aabb, manager[i]->m_aabb);
		if (check)
			return true;
	}
	return false;
}