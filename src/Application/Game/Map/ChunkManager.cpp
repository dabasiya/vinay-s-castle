#include "include/ChunkManager.h"
#include "include/BlockTexture.h"
#include "../Objects/Managers/include/DoorManager.h"
#include <iostream>
#include <Windows.h>

bool ChunkManager::ready = false;
bool ChunkManager::br = false;
bool ChunkManager::isRendering = false;

unsigned int ChunkManager::chunks_array_size = 0;

std::mutex ChunkManager::mut;

vector<vector<Chunk*>> ChunkManager::m_chunks;
vector<vector<ChunkData*>> ChunkManager::m_chunksdata;

ChunkManager::ChunkManager(unsigned int renderDistance) {
	m_renderDistance = renderDistance;

	chunks_array_size = (m_renderDistance * 2) + 1;
	glm::vec3 campos = Camera::GetPosition();
	long firstx = (campos.x < 0.0f) ? (long)campos.x / CHUNK_X_LENGTH - 1 : (long)campos.x/CHUNK_X_LENGTH;
	long firstz = (campos.z < 0.0f) ? (long)campos.z / CHUNK_Z_LENGTH - 1 : (long)campos.z/CHUNK_Z_LENGTH;

	firstx -= renderDistance;
	firstz -= renderDistance;

	for (long i = 0; i < chunks_array_size; i++) {
		vector<Chunk*> xs;
		vector<Batch*> xbs;
		vector<ChunkData*> xcd;
		for (long j = 0; j < chunks_array_size; j++) {
			Chunk* a = new Chunk((j+firstx) * CHUNK_X_LENGTH, 0, (i+firstz) * CHUNK_Z_LENGTH);
			a->isready = false;
			xs.push_back(a);
			Batch* b = new Batch(CHUNK_VERTEX_BUFFER_BATCH_SIZE);
			xbs.push_back(b);
			ChunkData* c = new ChunkData();
			xcd.push_back(c);
		}
		m_chunks.push_back(xs);
		m_chunksdata.push_back(xcd);
		m_batchs.push_back(xbs);
		xs.clear();
		xcd.clear();
		xbs.clear();
	}
	

	ready = false;


	updaterthread = std::thread(&ChunkManager::UpdateChunksThreadFunction, this);
}

unsigned short ChunkManager::get(long x, long y, long z) {
	if (y < 0 || y >= CHUNK_Y_LENGTH)
		return 0;
	long offsetx = m_chunks[0][0]->m_offsetx;
	long offsetz = m_chunks[0][0]->m_offsetz;


	long tx = (x - offsetx);
	long tz = (z - offsetz);


	if (tx < 0 || tx >= 16*chunks_array_size || tz < 0 || tz >= 16*chunks_array_size)
		return Noise::Noise3D(x, y, z);


	int cxindex = tx / CHUNK_X_LENGTH;
	int czindex = tz / CHUNK_Z_LENGTH;


	return m_chunks[czindex][cxindex]->get(tx % CHUNK_X_LENGTH, y % CHUNK_Y_LENGTH, tz % CHUNK_Z_LENGTH);
}

void ChunkManager::set(long x, long y, long z, unsigned short value) {
	long offsetx = m_chunks[0][0]->m_offsetx;
	long offsety = m_chunks[0][0]->m_offsety;
	long offsetz = m_chunks[0][0]->m_offsetz;

	long tx = (x - offsetx);
	long ty = (y - offsety);
	long tz = (z - offsetz);


	int cxindex = tx / CHUNK_X_LENGTH;
	int czindez = tz / CHUNK_Z_LENGTH;

	m_chunks[czindez][cxindex]->set(tx % CHUNK_X_LENGTH, ty % CHUNK_Y_LENGTH, tz % CHUNK_Z_LENGTH,value);
}

void ChunkManager::Update() {
	mut.lock();
	canupdatedata = false;
	if (x_negative || x_positive) {
		for (int i = 0; i < chunks_array_size; i++) {
			Batch* temp = new Batch(CHUNK_VERTEX_BUFFER_BATCH_SIZE);
			if (x_negative) {
				m_batchs[i][chunks_array_size - 1]->Delete();
				delete m_batchs[i][chunks_array_size - 1];
				m_batchs[i].pop_back();
				m_batchs[i].insert(m_batchs[i].begin(), temp);
			}
			else if (x_positive) {
				m_batchs[i][0]->Delete();
				delete m_batchs[i][0];
				m_batchs[i].erase(m_batchs[i].begin());
				m_batchs[i].push_back(temp);
			}
		}
		x_negative = false;
		x_positive = false;
	}

	else if (z_negative || z_positive) {
		vector<Batch*> b;
		for (int i = 0; i < chunks_array_size; i++) {
			Batch* temp = new Batch(CHUNK_VERTEX_BUFFER_BATCH_SIZE);
			if (z_negative) {
				m_batchs[chunks_array_size - 1][i]->Delete();
				delete m_batchs[chunks_array_size - 1][i];
			}
			else if (z_positive) {
				m_batchs[0][i]->Delete();
				delete m_batchs[0][i];
			}
			b.push_back(temp);
		}
		if (z_negative) {
			m_batchs.insert(m_batchs.begin(), b);
			m_batchs.pop_back();
		}
		else if (z_positive) {
			m_batchs.erase(m_batchs.begin());
			m_batchs.push_back(b);
		}

		z_negative = false;
		z_positive = false;
	}
	for (int i = 0; i < chunks_array_size; i++) {
		for (int j = 0; j < chunks_array_size; j++) {
			if (m_chunks[i][j]->m_isChanged && m_chunks[i][j]->isready && m_chunks[i][j]->isVisibletoCamera()) {
				m_batchs[i][j]->CleanVertices();
				//m_batchs[i][j][k]->ready = false;
				m_chunks[i][j]->m_isChanged = false;
				m_batchs[i][j]->UpdateVertices(0, m_chunksdata[i][j]->data.size() * 4, m_chunksdata[i][j]->data.data());

				
				DoorManager::mut.lock();
				for (int k = 0; k < DoorManager::manager.size(); k++) {
					if (DoorManager::manager[k]->x >= m_chunks[i][j]->m_offsetx && DoorManager::manager[k]->x < m_chunks[i][j]->m_offsetx + CHUNK_X_LENGTH &&
						DoorManager::manager[k]->z >= m_chunks[i][j]->m_offsetz && DoorManager::manager[k]->z < m_chunks[i][j]->m_offsetz + CHUNK_Z_LENGTH) {

						AddVertices(DoorManager::manager[k]->getVertices().data(),56 * 6 * 4, DoorManager::manager[k]->x, DoorManager::manager[k]->y, DoorManager::manager[k]->z);

					}
				}
				DoorManager::mut.unlock();
				
			}
		}
	}
	mut.unlock();
}




void ChunkManager::Render(Shader* shader) {
	renderedchunks = 0;
	for (int i = 0; i < chunks_array_size; i++) {
		for (int j = 0; j < chunks_array_size; j++) {
			m_batchs[i][j]->Render(shader);
			renderedchunks++;
		}
	}
}

void ChunkManager::RenderVisible(Shader* shader) {
	renderedchunks = 0;
	for (int i = 0; i < chunks_array_size; i++) {
		for (int j = 0; j < chunks_array_size; j++) {
			if (m_chunks[i][j]->isVisibletoCamera()) {
				m_batchs[i][j]->Render(shader);
				renderedchunks++;
			}
		}
	}
}

bool ChunkManager::isVisible(long x, long y, long z, unsigned int side) {
	// if coordinate is last outer then it will be not rendered
	if (y <= 0 && y >= CHUNK_Y_LENGTH-1)
		return true;

	switch (side) {
	case X_NEGATIVE:
		if (get(x - 1, y, z) == 0)
			return true;
		break;
	case X_POSITIVE:
		if (get(x + 1, y, z) == 0)
			return true;
		break;
	case Y_NEGATIVE:
		if (get(x, y - 1, z) == 0)
			return true;
		break;
	case Y_POSITIVE:
		if (get(x, y + 1, z) == 0)
			return true;
		break;
	case Z_NEGATIVE:
		if (get(x, y, z - 1) == 0)
			return true;
		break;
	case Z_POSITIVE:
		if (get(x, y, z + 1) == 0)
			return true;
		break;
	default:
		return false;
	}
	return false;
}

void ChunkManager::Delete() {
	
	isgamerunning = false;
	updaterthread.join();

	for (unsigned int i = 0; i < chunks_array_size; i++) {
		for (unsigned int j = 0; j < chunks_array_size; j++) {
			m_batchs[i][j]->Delete();
			m_chunksdata[i][j]->data.clear();
			m_chunks[i][j]->Delete();
			delete m_batchs[i][j];
			delete m_chunks[i][j];
			delete m_chunksdata[i][j];
		}
	}
	m_chunks.clear();
	m_chunksdata.clear();
	m_batchs.clear();


	for (int i = 0; i < tvec.size(); i++) {
		while(!tvec[i].joinable()) {}
		tvec[i].join();
	}
}


unsigned int ChunkManager::getUpdatedChunkCount() {
	unsigned int count = 0;
	for (int i = 0; i < m_chunks.size(); i++) {
		for (int j = 0; j < m_chunks[0].size(); j++) {
			if (m_chunks[i][j]->m_isChanged)
				count++;
		}
	}
	return count;
}

void ChunkManager::UpdateChunksData() {
	for (unsigned int i = 0; i < chunks_array_size; i++) {
		for (unsigned int j = 0; j < chunks_array_size; j++) {
			if (m_chunks[i][j]->m_isChanged) {
				tvec.emplace_back(&ChunkManager::UpdateChunk, this, i, j);
			}
		}
	}
}


void ChunkManager::UpdateChunk(int i, int j) {
	m_chunks[i][j]->isready = false;
	m_chunksdata[i][j]->data.clear();
	for (int z = m_chunks[i][j]->m_offsetz; z < m_chunks[i][j]->m_offsetz + CHUNK_Z_LENGTH; z++) {
		for (int y = 0; y < CHUNK_Y_LENGTH; y++) {
			for (int x = m_chunks[i][j]->m_offsetx; x < m_chunks[i][j]->m_offsetx + CHUNK_X_LENGTH; x++) {
				unsigned short block = get(x, y, z);
				if (block > 0 && block < 1000) {
					for (int s = 0; s < 6; s++) {
						if (isVisible(x, y, z, s)) {
							std::vector<float> vd = BVG::GetBlockVertices((unsigned int)s, x, y, z, texcoords[block][0], texcoords[block][1], texcoords[block][2], texcoords[block][3]);
							for (int a = 0; a < 56; a++) {
								m_chunksdata[i][j]->data.push_back(vd[a]);
							}
							vd.clear();
						}
					}
				}
			}
		}
	}
	m_chunks[i][j]->isready = true;
}


void ChunkManager::UpdateChunksThreadFunction() {
	while (isgamerunning) {
		int mid_index = chunks_array_size / 2;
		mut.lock();
		// append chunks on x negative side
		if (Camera::GetPosition().x < m_chunks[0][mid_index]->m_offsetx) {
			x_negative = true;
			for (unsigned int i = 0; i < chunks_array_size; i++) {
				Chunk* a = new Chunk(m_chunks[i][0]->m_offsetx - CHUNK_X_LENGTH, m_chunks[i][0]->m_offsety, m_chunks[i][0]->m_offsetz);
				ChunkData* b = new ChunkData();

				m_chunks[i][chunks_array_size-1]->Delete();
				delete m_chunks[i][chunks_array_size - 1];
				m_chunksdata[i][chunks_array_size - 1]->data.clear();
				delete m_chunksdata[i][chunks_array_size - 1];

				m_chunks[i].pop_back();
				m_chunksdata[i].pop_back();
				m_chunks[i].insert(m_chunks[i].begin(), a);
				m_chunksdata[i].insert(m_chunksdata[i].begin(), b);
			}
		}

		// append chunks on x positive side
		else if (Camera::GetPosition().x > m_chunks[0][mid_index]->m_offsetx + CHUNK_X_LENGTH) {
			x_positive = true;
			for (unsigned int i = 0; i < chunks_array_size; i++) {
				Chunk* a = new Chunk(m_chunks[i][chunks_array_size - 1]->m_offsetx + CHUNK_X_LENGTH, m_chunks[i][chunks_array_size - 1]->m_offsety, m_chunks[i][chunks_array_size - 1]->m_offsetz);
				ChunkData* b = new ChunkData();

				m_chunks[i][0]->Delete();
				delete m_chunks[i][0];
				m_chunksdata[i][0]->data.clear();
				delete m_chunksdata[i][0];

				m_chunks[i].erase(m_chunks[i].begin());
				m_chunksdata[i].erase(m_chunksdata[i].begin());
				m_chunks[i].push_back(a);
				m_chunksdata[i].push_back(b);
			}
		}

		// append chunks on z negative side
		else if (Camera::GetPosition().z < m_chunks[mid_index][0]->m_offsetz) {
			z_negative = true;
			vector<Chunk*> vic;
			vector<ChunkData*> vicd;
			for (unsigned int i = 0; i < chunks_array_size; i++) {
				Chunk* a = new Chunk(m_chunks[0][i]->m_offsetx, m_chunks[0][i]->m_offsety, m_chunks[0][i]->m_offsetz - CHUNK_Z_LENGTH);
				ChunkData* b = new ChunkData();

				m_chunks[chunks_array_size-1][i]->Delete();
				delete m_chunks[chunks_array_size - 1][i];
				m_chunksdata[chunks_array_size - 1][i]->data.clear();
				delete m_chunksdata[chunks_array_size - 1][i];

				vic.push_back(a);
				vicd.push_back(b);
			}

			m_chunks.pop_back();
			m_chunksdata.pop_back();
			m_chunks.insert(m_chunks.begin(), vic);
			m_chunksdata.insert(m_chunksdata.begin(), vicd);
			vic.clear();
			vicd.clear();
		}

		// append chunks on z positive side
		else if (Camera::GetPosition().z > m_chunks[mid_index][0]->m_offsetz + CHUNK_Z_LENGTH) {
			z_positive = true;
			vector<Chunk*> vic;
			vector<ChunkData*> vicd;
			for (unsigned int i = 0; i < chunks_array_size; i++) {
				Chunk* a = new Chunk(m_chunks[chunks_array_size - 1][i]->m_offsetx, m_chunks[chunks_array_size - 1][i]->m_offsety, m_chunks[chunks_array_size - 1][i]->m_offsetz + CHUNK_Z_LENGTH);
				ChunkData* b = new ChunkData();

				m_chunks[0][i]->Delete();
				delete m_chunks[0][i];
				m_chunksdata[0][i]->data.clear();
				delete m_chunksdata[0][i];

				vic.push_back(a);
				vicd.push_back(b);
			}

			m_chunks.erase(m_chunks.begin());
			m_chunksdata.erase(m_chunksdata.begin());
			m_chunks.push_back(vic);
			m_chunksdata.push_back(vicd);
			vic.clear();
			vicd.clear();
		}
		
		UpdateChunksData();


		for (int i = 0; i < tvec.size(); i++) {
			if (tvec[i].joinable()) {
				tvec[i].join();
				tvec.erase(tvec.begin() + i);
				i--;
			}
		}

		mut.unlock();
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}


void ChunkManager::AddVertices(void* data, unsigned int size, long x, long y, long z) {
	x -= m_chunks[0][0]->m_offsetx;
	z -= m_chunks[0][0]->m_offsetz;

	int xi = x / CHUNK_X_LENGTH;
	int zi = z / CHUNK_Z_LENGTH;

	
	m_batchs[zi][xi]->UpdateVertices(m_batchs[zi][xi]->vertices_pointer, size, data);
}

