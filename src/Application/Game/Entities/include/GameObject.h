#pragma once

#include "../../../../glm.h"

class GameObject {
public:
	GameObject();
	//virtual ~GameObject();

	//virtual void Input();
	//virtual void Update();

	static bool isCollide(GameObject& a, GameObject& b);
	bool isCollideWithMap();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Velocity;
	glm::vec3 m_size;
};