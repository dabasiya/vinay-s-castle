#include "include/Game.h"
#include <iostream>

#define ax_pixel (1.0f/1024)
#define ay_pixel (1.0f/1024)

bool Game::isRunning = true;

Game::Game() {
	isRunning = true;
	playerShader = new Shader("src/Application/Game/res/Shaders/Player.vert", "src/Application/Game/res/Shaders/Player.frag");
	mapShader = new Shader("src/Application/Game/res/Shaders/Map.vert", "src/Application/Game/res/Shaders/Map.frag");
	texture = new Texture("src/Application/Game/res/texture.png",GL_RGBA);
	normalstexture = new Texture("src/Application/Game/res/texture_normals.png", GL_RGB);
	heightmaptexture = new Texture("src/Application/Game/res/texture_heightmap.png", GL_RGB);


	shader = new Shader("src/Application/FontRenderer/res/Shaders/2d.vert", "src/Application/FontRenderer/res/Shaders/2d.frag");

	m_fr = new FontRenderer();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));

	player = new Player(glm::vec3(0.0f,5.0f,0.0f));

	novisiblechunk = Box2D(0.0f, 0.0f, cshowsize, cshowsize, 0.0f, 1.0f - ay_pixel * 8, 8 * ax_pixel, 1.0f - ay_pixel * 16);
	visiblechunk = Box2D(0.0f, 0.0f, cshowsize, cshowsize, 8 * ax_pixel, 1.0f - ay_pixel * 8, 16 * ax_pixel, 1.0f - ay_pixel * 16);

	m_crosshair = new Box2D(0.0f, 0.0f, 0.05f, 0.05f, 64 * ax_pixel, 1.0f, 80 * ax_pixel, 1.0f - (16 * ay_pixel));

	map = new Map();

	lightpos = glm::vec3(0.0f);


}

void Game::Input() {
	if (glfwGetKey(Window::Get(), GLFW_KEY_ESCAPE) == GLFW_TRUE) {
		GameMenu gamemenu;
		gamemenu.Run();
	}

	camera.Input();
	player->Input();
}

void Game::Render() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// ~for testing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, Window::GetWidth(), Window::GetHeight());

	glEnable(GL_CULL_FACE);


	texture->Bind();
	playerShader->Bind();
	camera.SetViewAndProjection(playerShader);
	player->Render(playerShader);



	
	mapShader->Bind();
	mapShader->SetVec3("lightpos", lightpos);
	mapShader->SetVec3("camerapos", Camera::GetPosition());
	glActiveTexture(GL_TEXTURE0+0);
	texture->Bind();
	mapShader->Set1i("tex", 0);
	glActiveTexture(GL_TEXTURE0 + 1);
	normalstexture->Bind();
	mapShader->Set1i("normaltex", 1);
	
	camera.SetViewAndProjection(mapShader);
	map->Render(mapShader);
	//m_cm->Render(mapShader);
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	

	float xr = (float)Window::GetWidth() / (float)Window::GetHeight();
	float yr = (float)Window::GetHeight() / (float)Window::GetWidth();
	yr = 1.0f;

	shader->Bind();
	glm::mat4 projection1 = glm::mat4(1.0f);
	projection1 = glm::ortho(-xr, xr, -1.0f, 1.0f);
	shader->SetMat4("projection", projection1);

	
	float startx = xr - (cshowsize * map->m_cm->chunks_array_size);
	float starty = -1.0 + (map->m_cm->chunks_array_size * cshowsize);
	for (unsigned int i = 0; i < map->m_cm->chunks_array_size; i++) {
		for (unsigned int j = 0; j < map->m_cm->chunks_array_size; j++) {
			
			if (map->m_cm->m_chunks[i][j]->isVisibletoCamera() && map->m_cm->m_batchs[i][j]->vertices_pointer > 0) {
				visiblechunk.Render(shader, startx + (j * cshowsize), starty - (i * cshowsize));
			}
			else {
				novisiblechunk.Render(shader, startx + (j * cshowsize), starty - (i * cshowsize));
			}

		}
	}
	


	std::string str1 = "Vinay's Castle v1.0, Unlincesed Version :(";
	float cx = (float)(m_fr->getStringPixelWidth(str1) / 2) * 0.007f;
	m_fr->PrintString(str1, -xr + cx, yr - 0.03f, 0.007f);

	std::string str = "Position(" + std::to_string((int)Camera::GetPosition().x) + ", " + std::to_string((int)Camera::GetPosition().y) + ", " + std::to_string((int)Camera::GetPosition().z) + ")";
	cx = (float)(m_fr->getStringPixelWidth(str) / 2) * 0.007f;
	m_fr->PrintString(str, -xr + cx, yr - 0.10f , 0.007f);

	std::string chunkupdatestr = std::to_string(map->updatedchunkcount) + " Chunk Updates";
	cx = (float)(m_fr->getStringPixelWidth(chunkupdatestr) / 2) * 0.007f;
	m_fr->PrintString(chunkupdatestr, -xr + cx, yr - 0.17f, 0.007f);

	std::string renderedchunksstr = "Rendered Chunks : " + std::to_string(map->renderedchunks);
	cx = (m_fr->getStringPixelWidth(renderedchunksstr) / 2) * 0.007f;
	m_fr->PrintString(renderedchunksstr, -xr + cx, yr - 0.24f, 0.007f);


	m_crosshair->Render(shader, -0.05f/2, 0.05f/2);

	current_time = glfwGetTime();
	double timediff = current_time - last_time;
	counter++;
	if (timediff > 1.0 / 60.0) {
		fps = (1.0f / timediff) * counter;
		counter = 0;
		last_time = current_time;
	}

	std::string fpsstr = "FPS: " + to_string(fps);
	cx = (m_fr->getStringPixelWidth(fpsstr) / 2) * 0.007f;
	m_fr->PrintString(fpsstr, -xr + cx, yr - 0.31f, 0.007f);


	glfwSwapBuffers(Window::Get());
	glfwPollEvents();
}

void Game::Update(){
	map->Update();
	player->Update();
	lightpos = Camera::GetPosition() + glm::vec3(0.0f, 5.0f, 0.0f);
}

void Game::Delete() {
	player->Delete();
	mapShader->Delete();
	texture->Delete();
	playerShader->Delete();
	m_fr->Delete();
	map->Delete();
	m_crosshair->Delete();
	visiblechunk.Delete();
	novisiblechunk.Delete();
	delete m_crosshair;
	delete player;
	delete mapShader;
	delete texture;
	delete playerShader;
	delete m_fr;
	delete map;
}

void Game::Run() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	std::string fps_str;
	glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Camera::SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	while (isRunning && !glfwWindowShouldClose(Window::Get())) {
		m_start_time = glfwGetTime();

		Input();
		if (!isRunning)
			break;
		Update();
		Render();

		
		
		m_remain_time = (1000 / FPS) - (glfwGetTime() - m_start_time) * 1000;
		if (m_remain_time > 0) {
			Sleep((int)m_remain_time);
		}
		
	}
	glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);
}