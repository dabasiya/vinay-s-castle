#pragma once

#include <GLFW/glfw3.h>

class Window {
private:
	static GLFWwindow* ID;
	static int width;
	static int height;
public:
	Window() {} // this is for declaration of Window object
	Window(const char* title, int width, int height);
	~Window();
	static GLFWwindow* Get(); // return GLFWWindow ptr 
	static void SetWindowSize(GLFWwindow* window,int width, int height);
	static int GetWidth();
	static int GetHeight();
};