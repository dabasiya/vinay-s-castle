#include "include/Door.h"
#include <irrKlang.h>

irrklang::ISoundEngine* se = irrklang::createIrrKlangDevice();

Door::Door(bool is_on_x_axis, bool is_on_positive_side, long x, long y, long z) {
	this->is_on_positive_side = is_on_positive_side;
	this->is_on_x_axis = is_on_x_axis;

	this->x = x;
	this->y = y;
	this->z = z;

	setAABB(is_on_x_axis, is_on_positive_side);
}

std::vector<float> Door::getVertices() {
	std::vector<float> data;

	if (is_on_x_axis && is_on_positive_side) {
		std::vector<float> vd;
		for (int i = 0; i < 6; i++) {
			if (i == Z_NEGATIVE || i == Z_POSITIVE) {
				vd = BVG::GetBlockVertices(i, x, y, z + 0.9f, 1.0f, 2.0f, 0.1f, 0.0f, 1.0f - (960 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			else {
				vd = BVG::GetBlockVertices(i, x, y, z + 0.9f, 1.0f, 2.0f, 0.1f, 0.0f, 1.0f - (976 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			copy(data, vd);
			vd.clear();
		}
	}

	else if (is_on_x_axis && !is_on_positive_side) {
		std::vector<float> vd;
		for (int i = 0; i < 6; i++) {
			if (i == Z_NEGATIVE || i == Z_POSITIVE) {
				vd = BVG::GetBlockVertices(i, x, y, z, 1.0f, 2.0f, 0.1f, 0.0f, 1.0f - (960 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			else {
				vd = BVG::GetBlockVertices(i, x, y, z, 1.0f, 2.0f, 0.1f, 0.0f, 1.0f - (976 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			copy(data, vd);
			vd.clear();
		}
	}

	else if (!is_on_x_axis && !is_on_positive_side) {
		std::vector<float> vd;
		for (int i = 0; i < 6; i++) {
			if (i == X_NEGATIVE || i == X_POSITIVE) {
				vd = BVG::GetBlockVertices(i, x, y, z, 0.1f, 2.0f, 1.0f, 0.0f, 1.0f - (960 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			else {
				vd = BVG::GetBlockVertices(i, x, y, z, 0.1f, 2.0f, 1.0f, 0.0f, 1.0f - (976 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			copy(data, vd);
			vd.clear();
		}
	}

	else if (!is_on_x_axis && is_on_positive_side) {
		std::vector<float> vd;
		for (int i = 0; i < 6; i++) {
			if (i == X_NEGATIVE || i == X_POSITIVE) {
				vd = BVG::GetBlockVertices(i, x + 0.9f, y, z, 0.1f, 2.0f, 1.0f, 0.0f, 1.0f - (960 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			else {
				vd = BVG::GetBlockVertices(i, x + 0.9f, y, z, 0.1f, 2.0f, 1.0f, 0.0f, 1.0f - (976 * ay_pixel), 16 * ax_pixel, 1.0f - (992 * ay_pixel));
			}
			copy(data, vd);
			vd.clear();
		}
	}

	return data;
}

void Door::copy(std::vector<float>& v1, std::vector<float>& v2) {
	for (int i = 0; i < v2.size(); i++) {
		v1.push_back(v2[i]);
	}
}


void Door::setAABB(bool is_on_x_axis, bool is_on_positive_side) {
	if (is_on_x_axis && is_on_positive_side) {
		m_aabb = AABB(x, y, z + 0.9f, 1.0f, 2.0f, 0.1f);
	}
	else if (is_on_x_axis && !is_on_positive_side) {
		m_aabb = AABB(x, y, z, 1.0f, 2.0f, 0.1f);
	}
	else if (!is_on_x_axis && !is_on_positive_side) {
		m_aabb = AABB(x, y, z, 0.1f, 2.0f, 1.0f);
	}
	else if (!is_on_x_axis && is_on_positive_side) {
		m_aabb = AABB(x + 0.9f, y, z, 0.1f, 2.0f, 1.0f);
	}
}

bool Door::isCollide(AABB aabb1, AABB aabb2) {
	return AABB::overlap(aabb1, aabb2);
}

void Door::changestate() {
	if (canchangestate) {
		isOpen = !isOpen;
		if (statechangethread.joinable())
			statechangethread.join();
		is_on_x_axis = !is_on_x_axis;
		is_on_positive_side = !is_on_positive_side;
		setAABB(is_on_x_axis, is_on_positive_side);
		statechangethread = std::thread(&Door::delayafterstatechange, this);
	}
}


void playDoorSound(bool forwhichstate) {
	if (forwhichstate) {
		se->play2D("src/Application/Game/res/Audio/Map/Door/Door close.wav");
	}
	else {
		se->play2D("src/Application/Game/res/Audio/Map/Door/Door close.wav");
	}
}

void Door::delayafterstatechange() {
	canchangestate = false;
	playDoorSound(isOpen);
	this_thread::sleep_for(std::chrono::milliseconds(1000));
	canchangestate = true;
}

