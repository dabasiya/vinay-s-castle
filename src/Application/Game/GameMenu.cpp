#include "include/GameMenu.h"
#include "include/Game.h"


GameMenu::GameMenu() {
	isRunning = true;

	fr = new FontRenderer();

	texture = new Texture("src/Application/Game/res/GameMenu_texture.png", GL_RGB);
	playButton = new Button(-0.4f, 0.0f, 0.8f, 0.1f, 0.0f, 1.0f, 64 * GAMEMENU_TEXTURE_AX, 1.0f - (GAMEMENU_TEXTURE_AY * 16));
	exitButton = new Button(-0.4f, -0.2f, 0.8f, 0.1f, 64 * GAMEMENU_TEXTURE_AX, 1.0f, 128 * GAMEMENU_TEXTURE_AX, 1.0f - (GAMEMENU_TEXTURE_AY * 16));

	shader = new Shader("src/Application/Menu/res/Shaders/2d.vert", "src/Application/Menu/res/Shaders/2d.frag");
}


void GameMenu::Input() {
	if (playButton->isClicked()) {
		isRunning = false;
	}

	if (exitButton->isClicked() || glfwWindowShouldClose(Window::Get())) {
		isRunning = false;
		Game::isRunning = false;
	}
}

void GameMenu::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	fr->PrintString("Game Menu", 0.0f, 0.4f, 0.020f);


	texture->Bind();
	if (playButton->UnderCursor())
		playButton->Render(shader, 1.0f);
	else
		playButton->Render(shader, 0.8f);

	if (exitButton->UnderCursor())
		exitButton->Render(shader, 1.0f);
	else
		exitButton->Render(shader, 0.8f);

	glfwSwapBuffers(Window::Get());
	glfwPollEvents();
}


void GameMenu::Run() {
	glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glDisable(GL_CULL_FACE);
	glActiveTexture(GL_TEXTURE0 + 2);
	texture->Bind();
	shader->Bind();
	shader->Set1i("tex", 2);
	while (isRunning) {

		Input();

		float xr = (float) Window::GetWidth() / Window::GetHeight();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::ortho(-xr, xr, -1.0f, 1.0f);
		shader->Bind();
		shader->SetMat4("projection", projection);
		shader->SetFloat("opacity", 1.0f);
		Render();

	}
	Delete();
	glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_CULL_FACE);
}

void GameMenu::Delete() {
	delete texture;
	delete playButton;
}