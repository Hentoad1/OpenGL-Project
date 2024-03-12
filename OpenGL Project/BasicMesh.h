#pragma once

#include "BasicShader.h"


#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2

class Mesh {
	
public:
	Mesh(const std::string path);

	~Mesh();

	void Render();

private:
	void Load(const std::string path);

	ShaderProgram* shader;

	std::vector<std::pair<unsigned int, unsigned int>> mesh_indices;

	GLuint VAO;

	std::vector<float> positions;
	std::vector<float> textures;
	std::vector<float> normals;

	std::vector<unsigned int> indices;
};