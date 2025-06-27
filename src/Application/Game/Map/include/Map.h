#pragma once

#include "ChunkManager.h"
#include "../../Objects/Managers/include/DoorManager.h"

class Map {
private:
	//ChunkManager *m_cm;
public:
	ChunkManager* m_cm;
	unsigned int updatedchunkcount = 0;
	unsigned int renderedchunks = 0;
	bool test = true;
	Map();
	void Update();
	void Render(Shader* shader);
	void Delete();
};