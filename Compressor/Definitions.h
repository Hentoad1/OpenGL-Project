#pragma once

#include "pch.h"

#include "Macros.h"

struct Buffer {

	//pointer to the data.
	void* data;

	//size in bytes.
	size_t size;
};

struct Vertex {
	float position_x;
	float position_y;
	float position_z;

	float texture_x;
	float texture_y;

	float normal_x;
	float normal_y;
	float normal_z;
};

struct bVertex {
	float position_x;
	float position_y;
	float position_z;

	float texture_x;
	float texture_y;

	float normal_x;
	float normal_y;
	float normal_z;

	int32_t boneIndices[GLSL_MAX_BONE_INFLUENCE] = { -1, -1, -1, -1 };
	float boneWeights[GLSL_MAX_BONE_INFLUENCE] = { 0.0f, 0.0f, 0.0f, 0.0f };
};

struct Mesh {
	uint32_t indexCount;

	uint32_t BaseVertex;
	uint32_t BaseIndex;

	uint32_t materialIndex;

	glm::vec3 min;
	glm::vec3 max;
};

struct Color {
	float r;
	float g;
	float b;
	float a;
};

struct Texture {
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t bits_per_pixel = -1;
	void* data = nullptr; // width * height bytes
};

struct Material{

	Texture Diffuse_Texture;
	Texture Specular_Texture;
	Texture Ambient_Texture;

	Color Diffuse_Color;
	Color Specular_Color;
	Color Ambient_Color;
};