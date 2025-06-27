#pragma once

#include "Box2D.h"
#include "../../../Renderer/include/Window.h"

class Button : public Box2D {

public:
	Button() {} // for declaration
	Button(float x, float y, float width, float height, float tx1, float ty1, float tx2, float ty2);
	bool UnderCursor();
	bool isClicked();
};