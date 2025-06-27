#include "include/Camera.h"
#include <iostream>

double Camera::phi = 180.0;
double Camera::theta = 90.0;

glm::vec3 Camera::position = glm::vec3(0.0f);
glm::vec3 Camera::orientation = glm::vec3(0.0f);
glm::vec3 Camera::up = glm::vec3(0.0f);


Camera::Camera(glm::vec3 _position) {
	orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	SetPosition(_position);
}

void Camera::SetPosition(glm::vec3 _position) {
	position = _position;
}

void Camera::SetViewAndProjection(Shader* shader) {
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(position, position+orientation, up);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)Window::GetWidth() / Window::GetHeight(), 0.1f, 160.0f);
	shader->Bind();
	shader->SetMat4("cameramat", projection * view);
}

glm::vec3 Camera::GetPosition() {
	return position;
}

glm::vec3 Camera::GetOrientation() {
	return orientation;
}

void Camera::Input() {
	if (glfwGetKey(Window::Get(), GLFW_KEY_W)) {
		position += orientation;
	}

	if (glfwGetKey(Window::Get(), GLFW_KEY_S)) {
		position -= orientation;
	}

	if (glfwGetKey(Window::Get(), GLFW_KEY_A)) {
		position -=glm::cross(orientation, up);
	}

	if (glfwGetKey(Window::Get(), GLFW_KEY_D)) {
		position +=glm::cross(orientation, up);
	}

	double cursorx, cursory;	// for store current cursor position

	glfwGetCursorPos(Window::Get(), &cursorx, &cursory);

	double offsetx = cursorx - lastx;
	double offsety = cursory - lasty;

	double speed = 0.5;

	phi -= offsetx * speed;
	theta += offsety * speed;

	if (phi < 0)
		phi = 359.0;
	else if (phi > 359)
		phi = 0.0;

	if (theta < 25)
		theta = 25;
	else if (theta > 140)
		theta = 140.0;

	glm::vec3 tempOrientation = glm::vec3(1.0f);
	tempOrientation.x = glm::sin(glm::radians(phi)) * glm::sin(glm::radians(theta));
	tempOrientation.y = glm::cos(glm::radians(theta));
	tempOrientation.z = glm::cos(glm::radians(phi)) * glm::sin(glm::radians(theta));
	orientation = tempOrientation;


	lastx = cursorx;
	lasty = cursory;

}


double Camera::getPhi() {
	return phi;
}

double Camera::getTheta() {
	return theta;
}