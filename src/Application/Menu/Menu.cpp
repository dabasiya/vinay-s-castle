#include "include/Menu.h"
#include <iostream>

Menu::Menu() {
	shader = new Shader("src/Application/Menu/res/Shaders/2d.vert","src/Application/Menu/res/Shaders/2d.frag");
	texture = new Texture("src/Application/Menu/res/texture.png",GL_RGBA);
	logotexture = new Texture("src/Application/Menu/res/logo.png", GL_RGBA);
	playButton = new Button(-0.2f,0.0f,0.4f,0.1f,0.0f,1.0f,pixel*32,1.0f-(8*pixel));
	logo = new Box2D(-0.15f*4, 0.6f, 0.15f * 8, 0.15f, 0.0f, 1.0f, 1.0f, 0.0f);

	glfwSetWindowSizeCallback(Window::Get(), &Window::SetWindowSize);

	m_fr = new FontRenderer();
}

void Menu::Input() {
	if (playButton->isClicked()) {
		isrunning = false;
		Game* game = new Game();
		game->Run();
		game->Delete();
		isrunning = true;
		glEnable(GL_BLEND);
	}

	else if (glfwGetKey(Window::Get(), GLFW_KEY_ESCAPE)) {
		isrunning = false;
	}
}

void Menu::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float xr = (float)Window::GetWidth() / Window::GetHeight();

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(-xr, xr, -1.0f, 1.0f);


	shader->Bind();
	glActiveTexture(GL_TEXTURE0);
	shader->SetFloat("opacity", 1.0f);
	shader->SetMat4("projection", projection);
	//shader->SetMat4("view", view);
	logotexture->Bind();
	logo->Render(shader);
	texture->Bind();
	if (playButton->UnderCursor())
		playButton->Render(shader, 1.0f);
	else
		playButton->Render(shader, 0.9f);

	

	glfwSwapBuffers(Window::Get());
	glfwPollEvents();
}

void Menu::Delete() {
	isrunning = false;
	shader->Delete();
	logo->Delete();
	playButton->Delete();
	texture->Delete();
	logotexture->Delete();
	m_fr->Delete();
	delete shader;
	delete logo;
	delete playButton;
	delete texture;
	delete logotexture;
	delete m_fr;
}

void Menu::Run() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (isrunning) {

		Input();
		Render();
	}
	glDisable(GL_BLEND);
}
