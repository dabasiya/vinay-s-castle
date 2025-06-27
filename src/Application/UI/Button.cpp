#include "include/Button.h"
#include <iostream>

Button::Button(float x, float y, float width, float height, float tx1, float ty1, float tx2, float ty2)
: Box2D(x, y, width, height, tx1, ty1, tx2, ty2) {
	
}



bool Button::UnderCursor() {
	double cursorx, cursory;
	glfwGetCursorPos(Window::Get(), &cursorx, &cursory);

	float r = (float)Window::GetWidth() / Window::GetHeight();

	float cursorxf = ((r*2 / Window::GetWidth()) * cursorx) - r;
	float cursoryf = -(((2.0f / Window::GetHeight()) * cursory) - 1.0f);

	if (cursorxf > getX() && cursorxf < getX() + getWidth() && cursoryf < getY() && cursoryf > getY() - getHeight()) {
		return true;
	}
	return false;
}

bool Button::isClicked() {
	if (glfwGetMouseButton(Window::Get(), GLFW_MOUSE_BUTTON_LEFT) && UnderCursor()) {
		return true;
	}
	return false;
}

