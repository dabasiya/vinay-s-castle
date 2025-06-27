#pragma once

#include "../../../Renderer/include/Camera.h"
#include "../../../Renderer/include/Window.h"
#include "../Entities/include/Player.h"
#include "../../../Renderer/include/Texture.h"
#include "../../../Renderer/include/Batch.h"
#include "../../FontRenderer/include/FontRenderer.h"
#include "../Map/include/Map.h"
#include "../../UI/include/Box2D.h"
#include "GameMenu.h"
#include <windows.h>
#include <mutex>

#define txp 1.0f/1024
#define typ 1.0f/1024

class Game {
private:
	int FPS = 60;
	FontRenderer* m_fr = NULL;
	double m_start_time = 0.0, m_remain_time = 0.0;
	double current_time = 0.0, last_time = 0.0;
	int counter = 0;
	int fps = 0;
	std::mutex mut;
	double m_last_fps_update_time = 0;
	glm::vec3 lightpos;
public:
	static bool isRunning;
	float cshowsize = 0.04f;
	Box2D visiblechunk, novisiblechunk;
	Box2D *m_crosshair = NULL;
	Camera camera;
	Game();
	Texture* texture = NULL, * normalstexture = NULL, * heightmaptexture = NULL;
	Shader *playerShader = NULL, *mapShader = NULL;
	Player* player = NULL;
	Shader* shader = NULL;
	Map* map;
	void Run();
	void Input();
	void Update();
	void Render();
	void Delete();

	const unsigned int SHADOW_WIDTH = 1024*4, SHADOW_HEIGHT = 1024*4;

};