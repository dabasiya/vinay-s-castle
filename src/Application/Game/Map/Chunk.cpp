#include "include/Chunk.h"
#include "../Objects/Managers/include/DoorManager.h"

Chunk::Chunk(long offsetx, long offsety, long offsetz) {
	Reset(offsetx, offsety, offsetz);
}

void Chunk::Reset(long offsetx, long offsety, long offsetz) {
	m_offsetx = offsetx;
	m_offsety = offsety;
	m_offsetz = offsetz;
	m_isChanged = true;

	for (int i = 0; i < CHUNK_Z_LENGTH; i++) {
		for (int j = 0; j < CHUNK_Y_LENGTH; j++) {
			for (int k = 0; k < CHUNK_X_LENGTH; k++) {
				m_array[i][j][k] = UINT16_MAX;
			}
		}
	}

	for (int i = 0; i < CHUNK_Z_LENGTH; i++) {
		for (int j = 0; j < CHUNK_Y_LENGTH; j++) {
			for (int k = 0; k < CHUNK_X_LENGTH; k++) {
				if (m_array[i][j][k] == UINT16_MAX) {
					m_array[i][j][k] = Noise::Noise3D(m_offsetx + k, m_offsety + j, m_offsetz + i);
					if (m_array[i][j][k] == 1) {
						if (i == 7 && j == 1) {
							DoorManager::addDoor(m_offsetx + k, m_offsety + j, m_offsetz + i, false, true);
							m_array[i][j][k] = 0;
							m_array[i][j + 1][k] = 0;
						}

						else if (k == 7 && j == 1) {
							DoorManager::addDoor(m_offsetx + k, m_offsety + j, m_offsetz + i, true, true);
							m_array[i][j][k] = 0;
							m_array[i][j + 1][k] = 0;
						}
					}
				}
			}
		}
	}
	isready = false;
}

unsigned short Chunk::get(unsigned char x, unsigned char y, unsigned char z) {
	return m_array[z][y][x];
}

void Chunk::set(unsigned char x, unsigned char y, unsigned char z, unsigned short value) {
	if (isready) {
		m_array[z][y][x] = value;
		m_isChanged = true;
	}
}


double Chunk::getAngle(glm::vec3 pos) {
	pos.y = 0.0f;
	glm::vec3 campos = Camera::GetPosition();
	campos.y = 0.0f;
	glm::vec3 v1 = pos - campos;

	glm::vec3 v2 = Camera::GetOrientation();
	v2.y = 0.0f;
	double a = glm::dot(v1, v2) / (getMagnitude(v1) * getMagnitude(v2));
	return a;
}

double Chunk::getMagnitude(glm::vec3 value) {
	double a = value.x * value.x + value.y * value.y + value.z * value.z;
	return sqrt(a);
}

bool Chunk::isVisibletoCamera() {
	glm::vec3 pos = Camera::GetPosition();

	if ((pos.x >= m_offsetx && pos.x < m_offsetx + CHUNK_X_LENGTH) && (pos.z >= m_offsetz && pos.z < m_offsetz + CHUNK_Z_LENGTH))
		return true;
	float y = 0.0f;
	if (getAngle(glm::vec3(m_offsetx, y, m_offsetz)) > cos(glm::radians(visibled)))
		return true;
	if (getAngle(glm::vec3(m_offsetx + CHUNK_X_LENGTH, y, m_offsetz)) > cos(glm::radians(visibled)))
		return true;
	if (getAngle(glm::vec3(m_offsetx, y, m_offsetz + CHUNK_Z_LENGTH)) > cos(glm::radians(visibled)))
		return true;
	if (getAngle(glm::vec3(m_offsetx + CHUNK_X_LENGTH, y, m_offsetz + CHUNK_Z_LENGTH)) > cos(glm::radians(visibled)))
		return true;
	return false;
}


void Chunk::Delete() {
	DoorManager::mut.lock();
	for (int i = 0; i < DoorManager::manager.size(); i++) {
		if ((DoorManager::manager[i]->x >= m_offsetx && DoorManager::manager[i]->x < m_offsetx + CHUNK_X_LENGTH) &&
			(DoorManager::manager[i]->z >= m_offsetz && DoorManager::manager[i]->z < m_offsetz + CHUNK_Z_LENGTH)) {
			if (DoorManager::manager[i]->statechangethread.joinable())
				DoorManager::manager[i]->statechangethread.join();
			delete DoorManager::manager[i];
			DoorManager::manager.erase(DoorManager::manager.begin() + i);
			i--;
		}
	}
	DoorManager::mut.unlock();
}