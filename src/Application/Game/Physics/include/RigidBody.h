#pragma once

// for physics and object movement

#include "AABB.h"
#include "../../Map/include/ChunkManager.h"
#include "../../Objects/Managers/include/DoorManager.h"

class RigidBody : public AABB {
private:
	glm::vec3 m_gravity = glm::vec3(0.0f, -0.2f, 0.0f);
	glm::vec3 m_velocity;
public:
	std::vector<std::thread> tvec;
	std::thread jumpthread;
	static std::mutex mt;
	bool canjump = true;
	RigidBody() {} // for declaration
	RigidBody(float x, float y, float z, float x_length, float y_length, float z_length);
	void Update();
	void AddForce(glm::vec3 value);
	void Jump();
};