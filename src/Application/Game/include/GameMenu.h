#pragma once

#include "../../UI/include/Button.h"
#include "../../FontRenderer/include/FontRenderer.h"

#define GAMEMENU_TEXTURE_AX 1.0f/256
#define GAMEMENU_TEXTURE_AY 1.0f/256

class GameMenu {
public:
	GameMenu();

	void Input();
	void Render();
	void Run();
	void Delete();
private:

	bool isRunning;

	FontRenderer* fr;

	Button *playButton, *exitButton;
	Texture* texture;

	Shader* shader;
};