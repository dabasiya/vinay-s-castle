#include "include/Map.h"



Map::Map() {
	m_cm = new ChunkManager(7);

}

void Map::Update() {
	m_cm->Update();
	updatedchunkcount = m_cm->getUpdatedChunkCount();
	renderedchunks = m_cm->renderedchunks;
}

void Map::Render(Shader* shader) {
	m_cm->RenderVisible(shader);
	//m_cm->Render(shader);
}

void Map::Delete() {
	m_cm->Delete();
	delete m_cm;
}