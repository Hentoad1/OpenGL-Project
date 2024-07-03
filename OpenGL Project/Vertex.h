#pragma once

#include "pch.h"

#include "Scene.h"

struct Vertex {
	Vertex(float, float, float, float, float, float, float, float);

	Vertex(const aiVector3D&, const aiVector3D&, const aiVector3D&);

	Vertex() {}

	~Vertex();


	void SetPosition(const glm::vec3&);
	void SetPosition(const aiVector3D&);

	void SetTexture(const glm::vec2&);
	void SetTexture(const aiVector3D&);

	void SetNormal(const glm::vec3&);
	void SetNormal(const aiVector3D&);

	glm::vec3 GetPosition() const;

	glm::vec2 GetTexture() const;

	glm::vec3 GetNormal() const;


	float position_x;
	float position_y;
	float position_z;

	float texture_x;
	float texture_y;

	float normal_x;
	float normal_y;
	float normal_z;
};

struct sVertex{
	sVertex(float, float, float, float, float, float, float, float);

	sVertex(const aiVector3D&, const aiVector3D&, const aiVector3D&);

	sVertex() {}

	~sVertex();


	void SetPosition(const glm::vec3&);
	void SetPosition(const aiVector3D&);

	void SetTexture(const glm::vec2&);
	void SetTexture(const aiVector3D&);

	void SetNormal(const glm::vec3&);
	void SetNormal(const aiVector3D&);

	glm::vec3 GetPosition() const;

	glm::vec2 GetTexture() const;

	glm::vec3 GetNormal() const;


	float position_x;
	float position_y;
	float position_z;

	float texture_x;
	float texture_y;

	float normal_x;
	float normal_y;
	float normal_z;

	int boneIndices[MAX_BONE_INFLUENCE] = { -1, -1, -1, -1 };
	float boneWeights[MAX_BONE_INFLUENCE] = { 0.0f, 0.0f, 0.0f, 0.0f };
};