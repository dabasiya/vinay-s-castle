#include "include/Player.h"
#include "../Map/include/ChunkManager.h"
#include "../Objects/Managers/include/DoorManager.h"
#include <iostream>
#include <windows.h>
glm::vec3 Player::m_position = glm::vec3(1.0f);

Player::Player(glm::vec3 position) {
	Player::m_position = position;

	// initalize player's body part 3d model

	m_head = new Block3D(-0.3f, 0.3f, -0.25f, 0.25f, -0.3f, 0.3f);
	// set head texture 
	m_head->SetTextureCoordinates(Z_POSITIVE, 0.0f, 1.0f, GTPX * 8, 1.0f - (GTPY * 8));
	m_head->SetTextureCoordinates(X_NEGATIVE, GTPX * 16, 1.0f, GTPX * 8, 1.0f - (GTPY * 8));
	m_head->SetTextureCoordinates(X_POSITIVE, GTPX * 8, 1.0f, GTPX * 16, 1.0f - (GTPY * 8));
	m_head->SetTextureCoordinates(Z_NEGATIVE, GTPX * 16, 1.0f, GTPX * 24, 1.0f - (GTPY * 8));
	m_head->SetTextureCoordinates(Y_POSITIVE, GTPX * 16, 1.0f, GTPX * 24, 1.0f - (GTPY * 8));
	m_head->SetTextureCoordinates(Y_NEGATIVE, GTPX * 24, 1.0f, GTPX * 32, 1.0f - (GTPY * 8));
	m_head->GenerateBlock3D();


	m_chest = new Block3D(-0.3f, 0.3f, 0.0f, 0.6f, -0.15f, 0.15f);
	// set player chest texture
	for (int i = 0; i < 6; i++) {
		if (i == Z_POSITIVE)
			continue;
		m_chest->SetTextureCoordinates(i, GTPX * 40, 1.0f, GTPX * 48, 1.0f - (GTPY * 8));
	}
	m_chest->SetTextureCoordinates(Z_POSITIVE, GTPX * 32, 1.0f, GTPX * 40, 1.0f - (GTPY * 8));
	m_chest->GenerateBlock3D();
	
	m_lefthand = new Block3D(0.3f, 0.55f, -0.55f, 0.15f, -0.15f, 0.15f);
	m_righthand = new Block3D(-0.55f, -0.3f, -0.55f, 0.15f, -0.15f, 0.15f);
	// set right hand and left hand texture
	for (int i = 0; i < 4; i++) {
		m_righthand->SetTextureCoordinates(i, GTPX * 48, 1.0f, GTPX * 56, 1.0f - (GTPY * 8));
		m_lefthand->SetTextureCoordinates(i, GTPX * 48, 1.0f, GTPX * 56, 1.0f - (GTPY * 8));
	}
	m_righthand->SetTextureCoordinates(5, GTPX * 40, 1.0f, GTPX * 48, 1.0f - (GTPY * 8));
	m_lefthand->SetTextureCoordinates(5, GTPX * 40, 1.0f, GTPX * 48, 1.0f - (GTPY * 8));
	m_righthand->SetTextureCoordinates(4, GTPX * 24, 1.0f, GTPX * 32, 1.0f - (GTPY * 8));
	m_lefthand->SetTextureCoordinates(4, GTPX * 24, 1.0f, GTPX * 32, 1.0f - (GTPY * 8));
	m_righthand->GenerateBlock3D();
	m_lefthand->GenerateBlock3D();

	m_leftleg = new Block3D(0.0f, 0.3f, -0.55f, 0.0f, -0.15f, 0.15f);
	m_rightleg = new Block3D(-0.3f, 0.0f, -0.55f, 0.0f, -0.15f, 0.15f);
	// set right and left leg texture
	for (int i = 0; i < 4; i++) {
		m_rightleg->SetTextureCoordinates(i, GTPX * 56, 1.0f, GTPX * 64, 1.0f - (GTPY * 8));
		m_leftleg->SetTextureCoordinates(i, GTPX * 56, 1.0f, GTPX * 64, 1.0f - (GTPY * 8));
	}
	m_rightleg->SetTextureCoordinates(5, GTPX * 16, 1.0f, GTPX * 24, 1.0f - (GTPY * 8));
	m_leftleg->SetTextureCoordinates(5, GTPX * 16, 1.0f, GTPX * 24, 1.0f - (GTPY * 8));
	m_rightleg->SetTextureCoordinates(4, GTPX * 24, 1.0f, GTPX * 32, 1.0f - (GTPY * 8));
	m_leftleg->SetTextureCoordinates(4, GTPX * 24, 1.0f, GTPX * 32, 1.0f - (GTPY * 8));
	m_leftleg->GenerateBlock3D();
	m_rightleg->GenerateBlock3D();

	rb = RigidBody(position.x, position.y, position.z, 0.4f, 1.7f, 0.4f);

	Camera::SetPosition(position);
	se = irrklang::createIrrKlangDevice();
	soundthread = thread(&Player::soundloop, this);
}

void Player::Input() {
	if (glfwGetKey(Window::Get(), GLFW_KEY_W)) {
		iswalking = true;

		glm::vec3 o = Camera::GetOrientation();
		o.y = 0.0f;
		rb.AddForce(o / 4.0f);
	}
	else if (glfwGetKey(Window::Get(), GLFW_KEY_S)) {
		iswalking = true;

		glm::vec3 o = Camera::GetOrientation();
		o.y = 0.0f;
		rb.AddForce(-o / 4.0f);
	}

	if (glfwGetKey(Window::Get(), GLFW_KEY_A)) {
		iswalking = true;
		glm::vec3 o = Camera::GetOrientation();
		o.y = 0.0f;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 dir = glm::cross(up, o);
		rb.AddForce(dir / 4.0f);
		inputrotation = 45.0f;
	}
	else if (glfwGetKey(Window::Get(), GLFW_KEY_D)) {
		iswalking = true;
		glm::vec3 o = Camera::GetOrientation();
		o.y = 0.0f;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 dir = -glm::cross(up, o);
		rb.AddForce(dir / 4.0f);
		inputrotation = -45.0f;
	}
	else {
		inputrotation = 0.0f;
	}

	if (glfwGetKey(Window::Get(), GLFW_KEY_SPACE)) {
		if (jumpstartsec < 1) {
			rb.AddForce(glm::vec3(0.0f, 1.3f, 0.0f));
			jumpstartsec++;
		}
	} 
	else {
		jumpstartsec = 0;
	}

	if (glfwGetMouseButton(Window::Get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_TRUE) {
		raycast();
	}

	if (glfwGetKey(Window::Get(), GLFW_KEY_F))
		third_person = false;
	else if (glfwGetKey(Window::Get(), GLFW_KEY_T))
		third_person = true;
}

void Player::Update() {
	WalkAnimationUpdate();
	rb.Update();
	m_position = rb.getPosition();
	if(!third_person)
		Camera::SetPosition(m_position + glm::vec3(0.0f,1.55f + glm::sin(glm::radians(m_righthand_degree*3))/7, 0.0f));
	else
		Camera::SetPosition(m_position + glm::vec3(0.0f, 1.55f, 0.0f) - (Camera::GetOrientation()*3.0f));
	iswalking = (
		glfwGetKey(Window::Get(), GLFW_KEY_W) ||
		glfwGetKey(Window::Get(), GLFW_KEY_A) ||
		glfwGetKey(Window::Get(), GLFW_KEY_S) ||
		glfwGetKey(Window::Get(), GLFW_KEY_D));
}

void Player::Render(Shader* shader) {
	glm::mat4 playerrotation = glm::mat4(1.0f);
	playerrotation = glm::rotate(playerrotation, (float)glm::radians(Camera::getPhi()), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->Bind();
	shader->SetMat4("extrarotation", playerrotation);
	m_head->Render(shader, m_position + glm::vec3(0.0f, 1.55f, 0.0f), Camera::getTheta() - 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	playerrotation = glm::mat4(1.0f);
	playerrotation = glm::rotate(playerrotation, (float)glm::radians(Camera::getPhi() + inputrotation), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->SetMat4("extrarotation", playerrotation);
	m_chest->Render(shader, m_position + glm::vec3(0.0f, 0.7f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_righthand->Render(shader, m_position + glm::vec3(0.0f, 1.15f, 0.0f), m_righthand_degree, glm::vec3(1.0f, 0.0f, 0.0f));
	m_lefthand->Render(shader, m_position + glm::vec3(0.0f, 1.15f, 0.0f), m_lefthand_degree, glm::vec3(1.0f, 0.0f, 0.0f));
	m_leftleg->Render(shader, m_position + glm::vec3(0.0f, 0.7f, 0.0f), m_leftleg_degree, glm::vec3(1.0f, 0.0f, 0.0f));
	m_rightleg->Render(shader, m_position + glm::vec3(0.0f, 0.7f, 0.0f), m_rightleg_degree, glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Player::getPosition() {
	return Player::m_position;
}

void Player::Delete() {
	isdestroyed = true;
	soundthread.join();
	se->drop();
	m_head->Delete();
	m_chest->Delete();
	m_righthand->Delete();
	m_lefthand->Delete();
	m_rightleg->Delete();
	m_leftleg->Delete();
	delete m_head;
	delete m_chest;
	delete m_righthand;
	delete m_lefthand;
	delete m_rightleg;
	delete m_leftleg;
}



void Player::WalkAnimationUpdate() {
	if (iswalking) {
		m_righthand_degree += m_rs;
		m_leftleg_degree += m_rs;

		m_lefthand_degree -= m_rs;
		m_rightleg_degree -= m_rs;

		if (m_righthand_degree > 75.0f)
			m_rs = -m_rs;
		else if (m_righthand_degree < -75.0f)
			m_rs = -m_rs;
	}


	else {
		m_rs = 10.0f;
		m_righthand_degree = 0.0f;
		m_leftleg_degree = 0.0f;
		m_lefthand_degree = 0.0f;
		m_rightleg_degree = 0.0f;
	}
}

void Player::raycast() {
	glm::vec3 rayposition = Camera::GetPosition();

	glm::vec3 unit = Camera::GetOrientation();

	int count = 0;
	DoorManager::mut.lock();
	while (count < 5) {
		rayposition += unit;
		long x = (long)floor(rayposition.x);
		long y = (long)floor(rayposition.y);
		long z = (long)floor(rayposition.z);

		bool found = false;
		int i = 0;
		while (!found && i < DoorManager::manager.size()) {
			if (DoorManager::manager[i]->x == x && (DoorManager::manager[i]->y == y || DoorManager::manager[i]->y == y - 1) && DoorManager::manager[i]->z == z) {
				found = true;
				count = 30;
				break;
			}
			i++;
		}
		if (found) {
			x -= ChunkManager::m_chunks[0][0]->m_offsetx;
			z -= ChunkManager::m_chunks[0][0]->m_offsetz;

			int xi = x / CHUNK_X_LENGTH;
			int zi = z / CHUNK_Z_LENGTH;


			DoorManager::manager[i]->changestate();

			ChunkManager::m_chunks[zi][xi]->m_isChanged = true;
		}
		count++;
	}
	DoorManager::mut.unlock();
}

void Player::soundloop() {
	while (!isdestroyed) {
		if (iswalking) {
			se->play2D("src/Application/Game/res/Audio/Player/walk.wav", true);
			while (iswalking) {
				Sleep(1);
			}
			se->removeSoundSource("src/Application/Game/res/Audio/Player/walk.wav");
		}
	}
}