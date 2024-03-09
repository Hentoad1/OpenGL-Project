#pragma once

#include "pch.h"

#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2

class Mesh {
	
public:
	Mesh(std::string path);

	~Mesh();

	void Render();

private:
	const aiScene* Load(std::string path);

	void GenBuffers(const aiScene* scene);


	std::vector<unsigned int> mesh_widths;

	GLuint VAO;
};