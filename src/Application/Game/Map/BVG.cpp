#include "include/BVG.h"
#include "../../../glm.h"

std::vector<float> BVG::GetBlockVertices(unsigned int side, float x, float y, float z, float tx1, float ty1, float tx2, float ty2) {
	return GetBlockVertices(side, x, y, z, 1.0f, 1.0f, 1.0f, tx1, ty1, tx2, ty2);
}


std::vector<float> BVG::GetBlockVertices(unsigned int side, float x, float y, float z, float x_length, float y_length, float z_length, float tx1, float ty1, float tx2, float ty2) {
	std::vector<float> data(56);
	glm::vec3 tangent, bitangent;
	glm::vec3 pos1, pos2, pos3, pos4;
	glm::vec2 uv1, uv2, uv3, uv4;


	if (side == Z_NEGATIVE) {
		pos1 = glm::vec3(x, y + y_length, z);
		pos2 = glm::vec3(x + x_length, y + y_length, z);
		pos3 = glm::vec3(x + x_length, y, z);
		pos4 = glm::vec3(x, y, z);

		uv1 = glm::vec2(tx2, ty1);
		uv2 = glm::vec2(tx1, ty1);
		uv3 = glm::vec2(tx1, ty2);
		uv4 = glm::vec2(tx2, ty2);
	}

	else if (side == X_POSITIVE) {
		pos1 = glm::vec3(x + x_length, y + y_length, z);
		pos2 = glm::vec3(x + x_length, y + y_length, z + z_length);
		pos3 = glm::vec3(x + x_length, y, z + z_length);
		pos4 = glm::vec3(x + x_length, y, z);


		uv1 = glm::vec2(tx1, ty1);
		uv2 = glm::vec2(tx2, ty1);
		uv3 = glm::vec2(tx2, ty2);
		uv4 = glm::vec2(tx1, ty2);
	}

	else if (side == Z_POSITIVE) {
		pos1 = glm::vec3(x + x_length, y + y_length, z + z_length);
		pos2 = glm::vec3(x, y + y_length, z + z_length);
		pos3 = glm::vec3(x, y, z + z_length);
		pos4 = glm::vec3(x + x_length, y, z + z_length);


		uv1 = glm::vec2(tx2, ty1);
		uv2 = glm::vec2(tx1, ty1);
		uv3 = glm::vec2(tx1, ty2);
		uv4 = glm::vec2(tx2, ty2);
	}

	else if (side == X_NEGATIVE) {
		pos1 = glm::vec3(x, y + y_length, z + z_length);
		pos2 = glm::vec3(x, y + y_length, z);
		pos3 = glm::vec3(x, y, z);
		pos4 = glm::vec3(x, y, z + z_length);


		uv1 = glm::vec2(tx1, ty1);
		uv2 = glm::vec2(tx2, ty1);
		uv3 = glm::vec2(tx2, ty2);
		uv4 = glm::vec2(tx1, ty2);
	}

	else if (side == Y_NEGATIVE) {
		pos1 = glm::vec3(x + x_length, y, z + z_length);
		pos2 = glm::vec3(x, y, z + z_length);
		pos3 = glm::vec3(x, y, z);
		pos4 = glm::vec3(x + x_length, y, z);


		uv1 = glm::vec2(tx2, ty1);
		uv2 = glm::vec2(tx1, ty1);
		uv3 = glm::vec2(tx1, ty2);
		uv4 = glm::vec2(tx2, ty2);
	}

	else if (side == Y_POSITIVE) {
		pos1 = glm::vec3(x, y + y_length, z + z_length);
		pos2 = glm::vec3(x + x_length, y + y_length, z + z_length);
		pos3 = glm::vec3(x + x_length, y + y_length, z);
		pos4 = glm::vec3(x, y + y_length, z);


		uv1 = glm::vec2(tx1, ty1);
		uv2 = glm::vec2(tx2, ty1);
		uv3 = glm::vec2(tx2, ty2);
		uv4 = glm::vec2(tx1, ty2);
	}


	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltauv1 = uv2 - uv1;
	glm::vec2 deltauv2 = uv3 - uv1;
	float f = 1.0f / (deltauv1.x * deltauv2.y - deltauv2.x * deltauv1.y);


	tangent.x = f * (deltauv2.y * edge1.x - deltauv1.y * edge2.x);
	tangent.y = f * (deltauv2.y * edge1.y - deltauv1.y * edge2.y);
	tangent.z = f * (deltauv2.y * edge1.z - deltauv1.y * edge2.z);

	bitangent.x = f * (-deltauv2.x * edge1.x + deltauv1.x * edge2.x);
	bitangent.y = f * (-deltauv2.x * edge1.y + deltauv1.x * edge2.y);
	bitangent.z = f * (-deltauv2.x * edge1.z + deltauv1.x * edge2.z);
	

	if (side == Z_NEGATIVE) {
		float array[] = {
			x,					y + y_length,		z,		0.0f,		0.0f,		-1.0f,		tx2,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y + y_length,		z,		0.0f,		0.0f,		-1.0f,		tx1,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y,					z,		0.0f,		0.0f,		-1.0f,		tx1,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,					y,					z,		0.0f,		0.0f,		-1.0f,		tx2,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z
		};
		memcpy(data.data(), array, sizeof(float) * 56);
		return data;
	}

	else if (side == X_POSITIVE) {
		float array[] = {
			x + x_length,		y + y_length,		z,					1.0f,		0.0f,		0.0f,		tx1,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y + y_length,		z + z_length,		1.0f,		0.0f,		0.0f,		tx2,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,	
			x + x_length,		y,					z + z_length,		1.0f,		0.0f,		0.0f,		tx2,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y,					z,					1.0f,		0.0f,		0.0f,		tx1,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z
		};
		memcpy(data.data(), array, sizeof(float) * 56);
		return data;
	}

	else if (side == Z_POSITIVE) {
		float array[] = {
			x + x_length,		y + y_length,		z + z_length,		0.0f,		0.0f,		1.0f,		tx2,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,					y + y_length,		z + z_length,		0.0f,		0.0f,		1.0f,		tx1,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,					y,					z + z_length,		0.0f,		0.0f,		1.0f,		tx1,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y,					z + z_length,		0.0f,		0.0f,		1.0f,		tx2,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z
		};
		memcpy(data.data(), array, sizeof(float) * 56);
		return data;
	}

	else if (side == X_NEGATIVE) {
		float array[] = {
			x,		y + y_length,		z + z_length,		-1.0f,		0.0f,		0.0f,		tx1,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,		y + y_length,		z,					-1.0f,		0.0f,		0.0f,		tx2,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,		y,					z,					-1.0f,		0.0f,		0.0f,		tx2,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,		y,					z + z_length,		-1.0f,		0.0f,		0.0f,		tx1,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z
		};
		memcpy(data.data(), array, sizeof(float) * 56);
		return data;
	}

	else if (side == Y_NEGATIVE) {
		float array[] = {
			x + x_length,		y,		z + z_length,		0.0f,		-1.0f,		0.0f,		tx2,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,					y,		z + z_length,		0.0f,		-1.0f,		0.0f,		tx1,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,	
			x,					y,		z,					0.0f,		-1.0f,		0.0f,		tx1,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y,		z,					0.0f,		-1.0f,		0.0f,		tx2,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z
		};
		memcpy(data.data(), array, sizeof(float) * 56);
		return data;
	}

	else if (side == Y_POSITIVE) {
		float array[] = {
			x,					y + y_length,		z + z_length,		0.0f,		1.0f,		0.0f,		tx1,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y + y_length,		z + z_length,		0.0f,		1.0f,		0.0f,		tx2,		ty1,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x + x_length,		y + y_length,		z,					0.0f,		1.0f,		0.0f,		tx2,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z,
			x,					y + y_length,		z,					0.0f,		1.0f,		0.0f,		tx1,		ty2,	tangent.x,	tangent.y,	tangent.z,	bitangent.x,	bitangent.y,	bitangent.z
		};
		memcpy(data.data(), array, sizeof(float) * 56);
		return data;
	}
	return data;
}