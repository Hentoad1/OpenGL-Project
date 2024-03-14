#pragma once

#include "BasicShader.h"

#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2

class Mesh {
	
public:
	Mesh(const std::string, Camera*);

	~Mesh();

	void Render();

private:
	void Load(const std::string);

	struct MeshMeta {
		MeshMeta(unsigned int, unsigned int, glm::vec3, glm::vec3);

		unsigned int baseIndex;
		unsigned int indexCount;

		glm::vec3 min;
		glm::vec3 max;

		glm::vec3 center;

	};
	
	//Bounding Box
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center;

	//Vertex Array Object
	GLuint VAO;

	//Camera
	Camera* mCamera;

	//Shader
	ShaderProgram* shader;

	//Submesh Metadata
	std::vector<MeshMeta> mesh_data;
	
};