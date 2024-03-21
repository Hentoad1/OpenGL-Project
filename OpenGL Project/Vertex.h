#pragma once

#include "pch.h"

struct Vertex{
	Vertex(float, float, float, float, float, float, float, float);

	Vertex(const aiVector3D&, const aiVector3D&, const aiVector3D&);

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