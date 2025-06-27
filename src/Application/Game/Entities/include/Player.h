#pragma once

#include "../../../../Renderer/include/Camera.h"
#include "../../Objects/include/Block3D.h"
#include "../../Map/include/BVG.h"
#include "../../Physics/include/RigidBody.h"
#include <thread>
#include <irrKlang.h>

class Player {
private:
	static glm::vec3 m_position; // player position

	Block3D *m_righthand = NULL, *m_lefthand = NULL;
	Block3D *m_rightleg = NULL, *m_leftleg = NULL;
	Block3D* m_head = NULL;
	Block3D* m_chest = NULL;

	float inputrotation = 0.0f;

	bool m_atRest = true;

	float m_rs = 10.0f;

	float m_righthand_degree = 0.0f, m_lefthand_degree = 0.0f;
	float m_rightleg_degree = 0.0f, m_leftleg_degree = 0.0f;
	float m_head_degree = 0.0f;

	RigidBody rb;

	bool isdestroyed = false;
	irrklang::ISound* s;
	irrklang::ISoundEngine* se;
	std::thread soundthread;
	bool iswalking = false;

	int jumpstartsec = 0;

public:
	bool third_person = false;
	Player() {}; // for declaration
	Player(glm::vec3 position);
	static glm::vec3 getPosition();
	static void Move(glm::vec3 value);
	void Update();
	void Input();
	void Render(Shader* shader);
	void WalkAnimationUpdate();
	void Delete();
	void soundloop();
	void raycast();
};