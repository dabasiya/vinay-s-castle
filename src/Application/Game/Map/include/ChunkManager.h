#pragma once

#include "../../../../Renderer/include/Batch.h"
#include "../../../../Renderer/include/Camera.h"
#include <mutex>
#include "ChunkData.h"
#include "BVG.h"
#include "Chunk.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

#define CHUNK_VERTEX_BUFFER_BATCH_SIZE 768 * 6 * 56 * sizeof(float)


class ChunkManager {
private:

	// render distance in chunks
	unsigned int m_renderDistance = 0;
	

	// 3d vector of batch renderer which render chunk
	static vector<vector<ChunkData*>> m_chunksdata;

	bool isgamerunning = true;
	
public:
	vector<vector<Batch*>> m_batchs;

	// 3d vector for store chunks
	static vector<vector<Chunk*>> m_chunks;
	static std::mutex mut;
	int renderedchunks = 0;
	bool canupdatedata = true;
	static bool isRendering;
	static bool br;
	static bool ready;
	thread updaterthread;
	std::vector<thread> tvec;
	static unsigned int chunks_array_size;

	bool x_negative = false, x_positive = false;
	bool z_negative = false, z_positive = false;
	ChunkManager() {} // for declaration
	ChunkManager(unsigned int renderDistance);
	static unsigned short get(long x, long y, long z);
	void Update();
	void UpdateChunksData();
	static unsigned int getUpdatedChunkCount();
	static void set(long x, long y, long z, unsigned short value);
	static bool isVisible(long x, long y, long z, unsigned int side);
	void Render(Shader* shader);
	void RenderVisible(Shader* shader);
	void UpdateChunksThreadFunction();
	void UpdateChunk(int i, int j);

	
	void AddVertices(void* data, unsigned int size, long x, long y, long z);
	void Delete();
};