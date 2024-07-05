#pragma once

#include "pch.h"
#include "Vertex.h"
#include "Material.h"
#include "MaterialBuffer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "BoundingBox.h"

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

enum VERTEX_TYPE : uint8_t {
	VERTEX_TYPE_BASIC,
	VERTEX_TYPE_SKELETAL,
};

struct ModelData {

	ModelData(ModelData& ref) {
		throw;
	}

	ModelData(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<SubMesh>& _mesh_data, const std::vector<Material*>& _Materials, Skeleton* _skeleton, std::vector<Animation*> _animations, StaticBoundingBox* _sbb, const glm::vec3& _min, const glm::vec3& _max) :
		vType(VERTEX_TYPE_BASIC),
		vertices(new std::vector<Vertex>(_vertices)),
		indices(_indices),
		mesh_data(_mesh_data),
		Materials(_Materials),
		skeleton(_skeleton),
		animations(_animations),
		sbb(_sbb),
		min(_min),
		max(_max)
	{}

	ModelData(const std::vector<sVertex>&_vertices, const std::vector<unsigned int>&_indices, const std::vector<SubMesh>&_mesh_data, const std::vector<Material*>&_Materials, Skeleton * _skeleton, std::vector<Animation*> _animations, StaticBoundingBox* _sbb, const glm::vec3 & _min, const glm::vec3 & _max) :
		vType(VERTEX_TYPE_SKELETAL),
		vertices(new std::vector<sVertex>(_vertices)),
		indices(_indices),
		mesh_data(_mesh_data),
		Materials(_Materials),
		skeleton(_skeleton),
		animations(_animations),
		sbb(_sbb),
		min(_min),
		max(_max)
	{}

	~ModelData(){

		if (vType == VERTEX_TYPE_BASIC) {
			delete static_cast<std::vector<Vertex>*>(vertices);
		}
		else if (vType == VERTEX_TYPE_SKELETAL){
			delete static_cast<std::vector<sVertex>*>(vertices);
		}

		for (int i = 0; i < Materials.size(); ++i) {
			delete Materials[i];
		}

		//skeleton and animations are deleted in the buffers object.
	}

	VERTEX_TYPE vType;
	void* vertices;
	

	std::vector<unsigned int> indices;

	std::vector<SubMesh> mesh_data;

	std::vector<Material*> Materials;

	Skeleton* skeleton;
	std::vector<Animation*> animations;

	StaticBoundingBox* sbb;

	glm::vec3 min;
	glm::vec3 max;

	glm::vec3 center() const { return (min + max) * 0.5f; }
};

struct ModelBuffers {

	~ModelBuffers() {
		//write this shit in here
		
		glDeleteVertexArrays(1, &VAO);

		for (int i = 0; i < MBO.size(); ++i) {
			delete MBO[i];
		}

		for (int i = 0; i < animations.size(); ++i) {
			delete animations[i];
		}

		delete sbb;

		delete skeleton;
	}

	//Vertex Array Object
	GLuint VAO;

	//Material Buffer Object
	std::vector<MaterialBuffer*> MBO;

	std::vector<SubMesh> mesh_data;

	Skeleton* skeleton;
	std::vector<Animation*> animations;

	StaticBoundingBox* sbb;

	glm::vec3 min;
	glm::vec3 max;

	glm::vec3 center() const { return (min + max) * 0.5f; }
};
