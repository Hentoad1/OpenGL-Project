#pragma once

#include "pch.h"
#include "Vertex.h"
#include "Material.h"
#include "MaterialBuffer.h"
#include "Skeleton.h"
#include "Animation.h"

#define POSITION_LOCATION 0
#define TEXTURE_LOCATION 1
#define NORMAL_LOCATION 2
#define BONE_INDEX_LOCATION 3
#define BONE_WEIGHT_LOCATION 4

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

	ModelData(const std::vector<Vertex>& _vertices, const  std::vector<unsigned int>& _indices, const std::vector<SubMesh>& _mesh_data, Skeleton* _skeleton, std::vector<Animation*> _animations, const glm::vec3& _min, const glm::vec3& _max) :
		vertices(_vertices),
		indices(_indices),
		mesh_data(_mesh_data),
		skeleton(_skeleton),
		animations(_animations),
		min(_min),
		max(_max)
	{}

	std::vector<Vertex> vertices;

	std::vector<unsigned int> indices;

	std::vector<SubMesh> mesh_data;

	std::vector<Material*> Materials;

	Skeleton* skeleton;
	std::vector<Animation*> animations;

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

	Skeleton* skeleton;
	std::vector<Animation*> animations;

	glm::vec3 min;
	glm::vec3 max;

	glm::vec3 center() const { return (min + max) * 0.5f; }
};
