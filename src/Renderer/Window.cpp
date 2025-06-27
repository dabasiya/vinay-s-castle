#include "include/Window.h"

int Window::width = 0;
int Window::height = 0;

GLFWwindow* Window::ID = NULL;


Window::Window(const char* title, int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_DECORATED, NULL);

	const GLFWvidmode* videomode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	this->width = videomode->width;
	this->height = videomode->height;
	ID = glfwCreateWindow(this->width, this->height, title, NULL, NULL);
	glfwMakeContextCurrent(ID);
}

Window::~Window() {
	glfwDestroyWindow(ID);
}

GLFWwindow* Window::Get() {
	return ID;
}

// for set window size

void Window::SetWindowSize(GLFWwindow* window, int width, int height) {
	Window::width = width;
	Window::height = height;
	glViewport(0, 0, width, height);
}

// return window width

int Window::GetWidth() {
	return width;
}

// return window height

int Window::GetHeight() {
	return height;
}