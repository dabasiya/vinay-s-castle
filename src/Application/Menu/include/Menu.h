#pragma once

#include "../../UI/include/Button.h"
#include "../../UI/include/Box2D.h"
#include "../../../Renderer/include/Texture.h"
#include "../../../Renderer/include/Shader.h"
#include "../../../Renderer/include/Window.h"
#include "../../Game/include/Game.h"
#include "../../FontRenderer/include/FontRenderer.h"
#include "irrKlang.h"
#include <thread>

#define pixel 1.0f/512

class Menu {
private:
	Button* playButton = NULL;
	Shader* shader = NULL;
	Texture *texture = NULL, *logotexture = NULL;
	Box2D* logo = NULL;
	FontRenderer* m_fr = NULL;
	bool isrunning = true;
public:
	Menu();
	void Input();
	void Render();
	void Delete();
	void Run();
};