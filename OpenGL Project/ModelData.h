#pragma once

#include "pch.h"
#include "Vertex.h"
#include "Material.h"
#include "MaterialBuffer.h"

#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2

#define UNIQUE_TEXTURE_TYPES 3

#define numTexTypes 3

struct SubMesh {
	unsigned int indexCount;

	unsigned int BaseVertex;
	unsigned int BaseIndex;

	unsigned int materialIndex;

	glm::vec3 min;
	glm::vec3 max;
};

struct ModelData {

	ModelData(ModelData& ref) {
		throw;
	}

	ModelData(const std::vector<Vertex>& _vertices, const  std::vector<unsigned int>& _indices, const std::vector<SubMesh>& _mesh_data, const glm::vec3& _min, const glm::vec3& _max) :
		vertices(_vertices),
		indices(_indices),
		mesh_data(_mesh_data),
		min(_min),
		max(_max)
	{}

	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	std::vector<SubMesh> mesh_data;

	std::vector<Material*> Materials;

	glm::vec3 min;
	glm::vec3 max;

	glm::vec3 center() const { return (min + max) * 0.5f; }
};

struct ModelBuffers {

	//Vertex Array Object
	GLuint VAO;

	//Material Buffer Object
	std::vector<MaterialBuffer*> MBO;

	std::vector<SubMesh> mesh_data;

	glm::vec3 min;
	glm::vec3 max;

	glm::vec3 center() const { return (min + max) * 0.5f; }
};
