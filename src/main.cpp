#include "Renderer/include/VAO.h"
#include "Renderer/include/VBO.h"
#include "Renderer/include/EBO.h"
#include "Renderer/include/Camera.h"
#include "Renderer/include/Shader.h"
#include "Renderer/include/Texture.h"
#include "Renderer/include/Window.h"
#include "Application/Game/Objects/include/Block3D.h"
#include "Renderer/include/Batch.h"
#include "Application/Game/Map/include/BVG.h"
#include "Application/Menu/include/Menu.h"
#include <windows.h>
#include <iostream>

int main() {
	Window window = Window("Vinay's Castle", 500, 500);
	gladLoadGL();
	
	Menu menu = Menu();
	menu.Run();
	menu.Delete();

}