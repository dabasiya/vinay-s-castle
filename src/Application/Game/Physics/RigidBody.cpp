#include "include/RigidBody.h"
#include <iostream>

std::mutex RigidBody::mt;

RigidBody::RigidBody(float x, float y, float z, float x_length, float y_length, float z_length)
: AABB(x, y, z, x_length, y_length, z_length)  {
	
}


void RigidBody::Update() {
	m_velocity += m_gravity;
	m_x += m_velocity.x;
	m_y += m_velocity.y;
	m_z += m_velocity.z;

	if (overlap_with_map_y()) {
		m_y += -m_gravity.y;
	}

	if (DoorManager::isCollide(*this)) {
		m_x -= m_velocity.x;
		m_z -= m_velocity.z;
	}

	else if (overlap_with_map_x() || overlap_with_map_z()) {
		m_x -= m_velocity.x;
		m_z -= m_velocity.z;
	}
	
	m_velocity = glm::vec3(0.0f);
}

void RigidBody::AddForce(glm::vec3 value) {
	m_velocity += value;
}

