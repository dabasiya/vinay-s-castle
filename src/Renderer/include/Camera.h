#pragma once

#include "Shader.h"
#include "../../glm.h"
#include "Window.h"

class Camera {
private:
	static glm::vec3 position;
	static glm::vec3 orientation;
	static glm::vec3 up;

	// for set orientation
	static double phi;
	static double theta;
	double lastx = Window::GetWidth() / 2;
	double lasty = Window::GetHeight() / 2;

public:
	Camera() {} // for declaration
	Camera(glm::vec3 _position);
	static void SetViewAndProjection(Shader* shader);
	static void SetPosition(glm::vec3 _position);
	static glm::vec3 GetOrientation();
	static glm::vec3 GetPosition();
	void Input();
	static double getTheta();
	static double getPhi();
};